/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:14:02 by guillemette       #+#    #+#             */
/*   Updated: 2023/03/29 10:38:03 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server(std::string name) : _name(name)
{
	this->_pollfds = std::vector<pollfd>(1);
// TO DO: change memset function with c++ equivalent
	memset(this->_svc, 0, NI_MAXSERV);
}

Server::Server(const Server& src) { *this = src; }

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Server::~Server(void) {}

/*
** --------------------------------- METHODS ----------------------------------
*/

void	Server::fillServerPollfd(void) {
	this->_pollfds[0].fd = this->_socket;
	this->_pollfds[0].events = POLLIN;
}

void	Server::createSocket(void) {

	this->_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socket == -1)
		std::cerr << "Can't create socket." << std::endl;
}

void	Server::_bind(sockaddr_in hint) {

	if (bind(this->_socket, (sockaddr*)&hint, sizeof(hint)) == -1)
		std::cerr << "Can't bind to IP/port." << std::endl;
}

void	Server::_listen(void) {

	if (listen(this->_socket, SOMAXCONN) == -1)
		std::cerr << "Can't listen." << std::endl;
	if (this->_socket == -1)
		std::cerr << "error getting listening socket" << std::endl;
}

void	Server::_accept(Client & client) {
// Accept the connection and set new client socket
	int newsocket;
	newsocket = accept(this->getSocket(), (sockaddr *)&client._sockaddr, &client._socklen);
	client.setSocket(newsocket);
	std::cout << "new Client " << inet_ntoa(client._sockaddr.sin_addr) << ":" << ntohs(client._sockaddr.sin_port) << " (" << client.getSocket() << ")" << std::endl;
}

void	Server::acceptNewClient()
{
	Client  client;
	this->_accept(client);
	struct pollfd newpollfd;
	newpollfd.fd = client.getSocket();
	newpollfd.events = POLLIN;
	this->_pollfds.push_back(newpollfd);
	// 1. Parse registration messages and get client nick, user and password
		// 1.1 Loop on buffer. When buffer finds \r\n>> create Message, handles Message, then empty buffer and go on with loop
		// 1.1.1 PASS > check if password is correct. if not skip the rest
		// 1.1.2 USER > check if user format is correct. if not skip the rest
		// 1.1.3 NICK > check if nick format is correct and if nick is not already used (ERR_NICKNAMEINUSE). If it is, register user (isRegistered = true). If not ???
	// 2- If correct registration, server sends block of welcome message
	char buf[BUFFER_SIZE];
	while (client.getRegistrationStatus() == false)
	{
		memset(buf,0, BUFFER_SIZE);
		recv(client.getSocket(), buf, sizeof(buf), 0);
		// std::cout << "[Client] (" << client.getSocket() << ")" << " received buf: " << buf << std::endl;
		std::vector<Message>  msgList = this->bufferParser(buf, client);
		execMultiMsg(msgList);
		// std::cout << "[Client] (" << client.getSocket() << ")" << " is now registered" << std::endl;
		if(this->_password != client.getPass())
		{
			std::cout << "pollserver: socket " << client.getSocket() << " hung up" << std::endl;
			close(client.getSocket()); // Bye!
			// this->getClients().erase(client.getSocket());
			return ;
		}
		client.setAsRegistered();
	}
	
	client.setPrefix();
	Replies replies(client);
	send(client.getSocket(), replies.RPL_WELCOME().data(), replies.RPL_WELCOME().size(), 0);
	send(client.getSocket(), replies.RPL_YOURHOST().data(), replies.RPL_YOURHOST().size(), 0);
	send(client.getSocket(), replies.RPL_CREATED().data(), replies.RPL_CREATED().size(), 0);
	send(client.getSocket(), replies.RPL_MYINFO().data(), replies.RPL_MYINFO().size(), 0);
	send(client.getSocket(), replies.RPL_MOTDSTART().data(), replies.RPL_MOTDSTART().size(), 0);
	// send(client.getSocket(), replies.RPL_MOTD("372").data(), replies.RPL_MOTD("372").size(), 0);
	replies.sendMotd(client.getSocket());
	send(client.getSocket(), replies.RPL_ENDOFMOTD().data(), replies.RPL_ENDOFMOTD().size(), 0);
	send(client.getSocket(), replies.RPL_UMODEIS().data(), replies.RPL_UMODEIS().size(), 0); // displays client's privileges
	// else deal with client registration issue
	this->getClients()[newpollfd.fd] = client;
}

void	Server::handleClientRequest(Client & client)
{
	// Handle other requests
	// WIP

	// PRIVATE MESSAGES BETWEEN CLIENTS
	char buf[BUFFER_SIZE];
	int nbytes = recv(client.getSocket(), buf, sizeof(buf), 0);
	if (nbytes <= 0)
	{
		// Got error or connection closed by client
		if (nbytes == 0)
			std::cout << "pollserver: socket " << client.getSocket() << " hung up" << std::endl;
		else
			perror("recv");
		close(client.getSocket()); // Bye!
		this->getClients().erase(client.getSocket()); // remove client from map
	}
	else
	{
		// Handle buffer as a vector of messages
		std::vector<Message>  msgList = this->bufferParser(buf, client);
		// std::cout << "[Client] (" << client.getSocket() << ")" << " received buf: " << buf << std::endl;
		// Execute all messages that could be parsed
		execMultiMsg(msgList);
	}
}

std::vector<std::string>	msg_split(std::string str, std::string delimiter)
{
	// std::vector<std::string> tokens = std::vector<std::string>();

	// size_t end;
	// while ((end = str.find(delimiter)) != std::string::npos || str == "\n")
	// {
	// 	tokens.push_back(str.substr(0, end));
	// 	str = str.substr(end + delimiter.size());
	// }
	// if (str != "")
	//     tokens.push_back(str);
	// return tokens;

	std::vector<std::string> tokens = std::vector<std::string>();

	int end;
	while ((end = str.find(delimiter)) != -1)
	{
		tokens.push_back(str.substr(0, end));
		str.erase(0, end + delimiter.length());
	}
	if (!str.empty())
	    tokens.push_back(str);
	return tokens;
}

void Server::msg_replace(std::string &message, char find, char replace){

    for(size_t i= 0; i < message.size(); i++){
        if(message[i]== find)
            message.replace(i, 1, 1, replace);
    }
}
// Parser buffer from char * to a vector of class Message
std::vector<Message>	Server::bufferParser(char* buf, Client &client){
	std::string                                     message(buf);
	std::vector<std::string>                        lines;
	std::vector<std::vector<std::string> >          tokens;
	std::vector<Message>                            msgList;
	size_t                                          msgSize = 0;

	// message = buf;
	msg_replace(message, 4, ' ');
	lines = msg_split(message, "\r\n");
	// Display lines vector
	msgSize = lines.size();
	for (size_t i = 0; i < msgSize; i++)
	{
		tokens.push_back(msg_split(lines[i], " "));
		Message msg(tokens[i], &client, this, lines[i]);
		msgList.push_back(msg);
	}
	return (msgList);
}

// excute every message
void					Server::execMultiMsg(std::vector<Message> msgList)
{
	for (size_t i=0; i < msgList.size(); ++i)
		msgList[i].execCmd();
}

/*
** --------------------------------- GETTERS ----------------------------------
*/

int						Server::getSocket(void) const
{

	return (this->_socket);
}

std::string				Server::getPassword(void) const
{
	return (this->_password);
}

std::map<int, Client>&	Server::getClients(void)
{
	return (this->_clients);
}

/* *************************setter************************************************* */
void Server::setPassword(char * password){_password = password;}