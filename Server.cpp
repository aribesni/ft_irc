/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchate <gduchate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:14:02 by guillemette       #+#    #+#             */
/*   Updated: 2023/03/24 16:12:52 by gduchate         ###   ########.fr       */
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
		recv(client.getSocket(), buf, sizeof(buf), 0);
		std::vector<Message>  msgList = this->bufferParser(buf, client);
		execMultiMsg(msgList);
	}
	client.setPrefix();
	Replies replies(client);
	send(client.getSocket(), replies.RPL_WELCOME("001").data(), replies.RPL_WELCOME("001").size(), 0);
	send(client.getSocket(), replies.RPL_YOURHOST("002").data(), replies.RPL_YOURHOST("002").size(), 0);
	send(client.getSocket(), replies.RPL_CREATED("003").data(), replies.RPL_CREATED("003").size(), 0);
	send(client.getSocket(), replies.RPL_MYINFO("004").data(), replies.RPL_MYINFO("004").size(), 0);
	send(client.getSocket(), replies.RPL_MOTDSTART("375").data(), replies.RPL_MOTDSTART("375").size(), 0);
	// send(client.getSocket(), replies.RPL_MOTD("372").data(), replies.RPL_MOTD("372").size(), 0);
	replies.sendMotd(client.getSocket());
	send(client.getSocket(), replies.RPL_ENDOFMOTD("376").data(), replies.RPL_ENDOFMOTD("376").size(), 0);
	// else deal with client registration issue
	this->clients[newpollfd.fd] = client;
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
		this->clients.erase(client.getSocket()); // remove client from map
	}
	else
	{
		// Handle buffer as a vector of messages
		std::vector<Message>  msgList = this->bufferParser(buf, client);
		std::cout << "[Client] (" << client.getSocket() << ")" << " received buf: " << buf << std::endl;
		// Execute all messages that could be parsed
		execMultiMsg(msgList);
		// std::map<int, Client>::iterator     _it;
		// for (_it = this->clients.begin(); _it != this->clients.end(); _it++)
		// {
		//     if (_it->first == client.getSocket()) // don't send message to client's own fd
		//         continue ;
		//     if (send(_it->first, buf, nbytes, 0) == -1) // send message to all the other clients fds
		//         perror("send");
		// }
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
	tokens.push_back(str);
	return tokens;
}


// Parser buffer from char * to a vector of class Message
std::vector<Message>	Server::bufferParser(char* buf, Client &client){
	std::string                                     message(buf);
	std::vector<std::string>                        lines;
	std::vector<std::vector<std::string> >          tokens;
	std::vector<Message>                            msgList;
	size_t                                          msgSize = 0;

	// message = buf;
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

int						Server::getSocket(void) const {

	return (this->_socket);
}

std::string				Server::getPassword(void) const
{
	return (this->_password);
}

/* ************************************************************************** */