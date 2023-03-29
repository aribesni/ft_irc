/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:43:49 by rliu              #+#    #+#             */
/*   Updated: 2023/03/27 16:56:44 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Command::Command(void){initCmdMap();}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/


Command::~Command(void){}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Command::initCmdMap()
{
	_cmdMap["PASS"] = &cmd_pass;
	_cmdMap["NICK"] = &cmd_nick;
	_cmdMap["USER"] = &cmd_user;
	_cmdMap["PING"] = &cmd_ping;
	_cmdMap["JOIN"] = &cmd_join;
	_cmdMap["PRIVMSG"] = &cmd_privmsg;
	_cmdMap["PART"] = &cmd_part;
    _cmdMap["OPER"] = &cmd_oper;
    _cmdMap["wallops"] = &cmd_wallops;
}

/*
** --------------------------------- utils---------------------------------
*/

void msgSender(Client &client, std::string cmd, std::string msg){
    std::string msgSend = ":"+client.getPrefix() + " " + cmd + " " + msg + "/r/n";
    send(client.getSocket(), msgSend.c_str(), msgSend.size(), 0);
}

std::string creatNickname(Client &client){
    std::ostringstream oOStrStream;
    oOStrStream << client.getSocket();
    
    std::string name = "Guest" + oOStrStream.str();
    return(name);
}
/*
** --------------------------------- COMMANDS ---------------------------------
*/


void cmd_pass(Message * message)
{
	if (message->getServer()->getPassword() != message->getParams()[0]){
		std::cout << "wrong password\n"; 
		return;
		// close(message->getServer()->getSocket()); // Bye!
		// message->getServer()->clients.erase(message->getServer()->getSocket()); 
    }
	else 
		message->getClient()->setPass( message->getParams()[0]);
       
}

void cmd_nick(Message * message)
{
	Replies reply(*(message->getClient()));
	std::string nick = message->getParams()[0];
    if (nick.size() > 9 || nick.empty()){
        nick = creatNickname(*(message->getClient()));
        send(message->getClient()->getSocket(),reply.ERR_ERRONEUSNICKNAME().c_str(), reply.ERR_ERRONEUSNICKNAME().size(), 0);
    }
	
    std::map<int, Client>::iterator     it;
    for (it = message->getServer()->getClients().begin(); it != message->getServer()->getClients().end(); it++)
    {
        if (it->first == message->getClient()->getSocket()) // don't send message to client's own fd
            continue ;
        if (nick == it->second.getNick()){
            nick = creatNickname(*(message->getClient()));
            send(message->getClient()->getSocket(),reply.ERR_NICKNAMEINUSE().c_str(), reply.ERR_NICKNAMEINUSE().size(), 0);
        }
    }
   	message->getClient()->setNick(message->getParams()[0]);
	if(nick != message->getParams()[0])
		msgSender(*(message->getClient()), "NICK", nick);
}

void cmd_user(Message * message)
{
	message->getClient()->setUsr(message->getParams()[0]);
	message->getClient()->setHostname(message->getParams()[2]);
	// To be edited afterwards depending on registration checks and put in the acceptNewClient func
	message->getClient()->setAsRegistered();
}

void cmd_ping(Message * message)
{
	// As a result of server correctly responding "PONG", the irssi client interface does not
	// show [LAG] message anymore
	std::cout << "[Server] sending PONG to client (" <<message->getClient()->getSocket() << ")" << std::endl;
	std::string answer = "PONG " + message->getParams()[0] + "\r\n";
	send(message->getClient()->getSocket(), answer.c_str(), answer.size(), 0);
}

void cmd_join(Message * message)
{
	// TO DO: handle channel password
	std::string chanName = message->getParams()[0];
	Server * server = message->getServer();
	Client * client = message->getClient();
	// if channel does not exist, create a Channel object, put it in the channel list and put client as chan op
	if (server->_channels.find(chanName) == server->_channels.end())
	{
		std::cout << "Channel " << chanName << " does not exist" << std::endl;
		Channel mychan(chanName, client);
		server->_channels[chanName] = mychan;
		// TO DO: First client is chan operator
		std::cout << "Channel " << chanName << " created and added to server list. User added to channel." << std::endl;
	}
	else
	{
		std::cout << "Channel " << chanName << " already exist" << std::endl;
		server->_channels[chanName].addClient(client);
		std::cout << "User added to channel." << std::endl;
	}
}

void cmd_part(Message * message)
{
	// Errors to be handled:
	// ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
    // ERR_NOTONCHANNEL
	std::string chanName = message->getParams()[0];
	Server * server = message->getServer();
	Client * client = message->getClient();
	// if channel does not exist, don't do anything
	if (server->_channels.find(chanName) == server->_channels.end())
	{
		std::cout << "Channel " << chanName << " does not exist" << std::endl;
	}
	else
	{
		std::cout << "Channel " << chanName << " already exist" << std::endl;
		server->_channels[chanName].removeClient(client);
		std::cout << "User removed from channel." << std::endl;
	}
}

// sendTo(irc::User &toUser, std::string message) { toUser.write(":" + this->getPrefix() + " " + message); }

void cmd_privmsg(Message * message)
{
//    the actual conversation carried out on a
//    channel is only sent to servers which are supporting users on a given
//    channel.  If there are multiple users on a server in the same
//    channel, the message text is sent only once to that server and then
//    sent to each client on the channel.  This action is then repeated for
//    each client-server combination until the original message has fanned
//    out and reached each member of the channel.


        //    ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
        //    ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
        //    ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
        //    ERR_NOSUCHNICK
        //    RPL_AWAY
	Server * server = message->getServer();
	Client * client = message->getClient();
	if (message->getParams().size() == 0)
	{
		Replies reply(*client);
		reply.ERR_NORECIPIENT(message->getCMD());
		return ;
	}
	std::string msgtarget = message->getParams()[0];

	if (msgtarget[0] == '#')
	{
		std::string fullMsg = ":" + client->getPrefix() + " " + message->getFullMsg() + "\r\n";
		std::cout << "Message sent to a channel" << std::endl;
		std::vector<Client*> listOfClients = server->_channels[msgtarget].getListOfClients();
		for (size_t i = 0; i < listOfClients.size(); i++)
		{
			if (listOfClients[i]->getSocket() != client->getSocket())
			{
				std::cout << "This client is in the chan: " << listOfClients[i]->getSocket() <<std::endl;
				std::cout << "This message is being sent: " << fullMsg << " to client " << listOfClients[i]->getSocket() << std::endl;
				send(listOfClients[i]->getSocket(), fullMsg.c_str(), fullMsg.size(), 0);
			}
		}
	}
	// if msgtarget starts with #>> it is a channel
	// 		search for client list in server
	// 		send to everyone expect oneself

	// if msgtarget does not start with #>> it is a user
	(void)message;
}

void    cmd_oper(Message * message) {

    Client * client = message->getClient();
    Replies replies(*client);

	if (message->getParams().size() < 2) // check if both <name> and <password> are entered
        send(client->getSocket(), replies.ERR_NEEDMOREPARAMS("OPER").data(), replies.ERR_NEEDMOREPARAMS("OPER").size(), 0);
    else if (message->getParams()[0] == "operator" && message->getParams()[1] == "password") // checks if <name> is set as "operator" and <password> as "password"
    {
        send(client->getSocket(), replies.RPL_YOUREOPER().data(), replies.RPL_YOUREOPER().size(), 0);
        client->setMode("wio"); // sets client's privileged to operator
        replies.setVariables(client); // updates client's new info
        send(client->getSocket(), replies.RPL_UMODEIS().data(), replies.RPL_UMODEIS().size(), 0); // displays new privileges
    }
    else
        send(client->getSocket(), replies.ERR_PASSWDMISMATCH().data(), replies.ERR_PASSWDMISMATCH().size(), 0); // wrong password
}

void    cmd_wallops(Message * message) {

    Client * client = message->getClient();
	Server * server = message->getServer();
    Replies replies(*client);
	size_t i = 0;

	std::string wallop = ":" + client->getPrefix() + " WALLOPS " + message->getParams()[0] + "\r\n";

    if (client->getMode() != "wio") // check if user has operator privileges
        send(client->getSocket(), replies.ERR_NOPRIVILEGES("Permission Denied- You're not an IRC operator").data(), replies.ERR_NOPRIVILEGES("Permission Denied- You're not an IRC operator").size(), 0);
	else
	{
		while (i < server->getClients().size())
		{
			if (server->getClients()[i].getMode().find("w") != std::string::npos) // check if client has "w" mode
				send(server->getClients()[i].getSocket(), wallop.data(), wallop.size(), 0); // sends message to all clients with "w" mode including the sender
			i++;
		}
	}
}

/* ************************************************************************** */