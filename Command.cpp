/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillemette.duchateau <guillemette.duch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:43:49 by rliu              #+#    #+#             */
/*   Updated: 2023/04/09 12:05:09 by guillemette      ###   ########.fr       */
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
    _cmdMap["OPER"] = &cmd_oper; /* grants the IRC operator status*/
    // _cmdMap["OP"] = &cmd_op; /* TO DO: grants the channel operator status*/
    _cmdMap["WALLOPS"] = &cmd_wallops;
    _cmdMap["KILL"] = &cmd_kill;
    _cmdMap["KICK"] = &cmd_kick;
    _cmdMap["NOTICE"] = &cmd_notice;
    _cmdMap["WHOIS"] = &cmd_whois;
    _cmdMap["INVITE"] = &cmd_invite;
    _cmdMap["MODE"] = &cmd_mode;
	// finir tous les messages d'erreurs
	// Check memory management


// Channel vs IRC operators

	// 1  The commands which may only be used by channel operators (user mode has "o" for given channel) are:
	//         KICK    - Eject a client from the channel
	//         MODE    - Change the channel's mode
	//         INVITE  - Invite a client to an invite-only channel (mode +i)
	//         TOPIC   - Change the channel topic in a mode +t channel


	// 2 KILL: only irc operator
}

/*
** --------------------------------- utils---------------------------------
*/

void msgSender(Client &client, std::string cmd, std::string msg){
    std::string msgSend = ":" +client.getPrefix() + " " + cmd + " " + msg + "/r/n";
    send(client.getSocket(), msgSend.c_str(), msgSend.size(), 0);
}

std::string createNickname(Client &client){
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
	// TO DO: ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED
	if (message->getServer()->getPassword() != message->getParams()[0]){
		std::cout << "wrong password\n";
		return;
    }
	else
		message->getClient()->setPass( message->getParams()[0]);
}

void cmd_nick(Message * message)
{
	//TO DO:    ERR_NONICKNAMEGIVEN      ERR_NICKCOLLISION
	Replies reply(*(message->getClient()));
	std::string nick = message->getParams()[0];
    if (nick.size() > 9 || nick.empty()){
        nick = createNickname(*(message->getClient()));
        send(message->getClient()->getSocket(),reply.ERR_ERRONEUSNICKNAME().c_str(), reply.ERR_ERRONEUSNICKNAME().size(), 0);
    }

    std::map<int, Client>::iterator     it;
    for (it = message->getServer()->getClients().begin(); it != message->getServer()->getClients().end(); it++)
    {
        if (it->first == message->getClient()->getSocket()) // don't send message to client's own fd
            continue ;
        if (nick == it->second.getNick()){
            nick = createNickname(*(message->getClient()));
            send(message->getClient()->getSocket(),reply.ERR_NICKNAMEINUSE().c_str(), reply.ERR_NICKNAMEINUSE().size(), 0);
        }
    }
   	message->getClient()->setNick(message->getParams()[0]);
	if(nick != message->getParams()[0])
		msgSender(*(message->getClient()), "NICK", nick);
}

void cmd_user(Message * message)
{
	// TO DO ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED
	message->getClient()->setUsr(message->getParams()[0]);
	message->getClient()->setHostname(message->getParams()[2]);
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
	// TO DO: handle multiple channels split with ,
	// User must provide a password if channel is key protected (k mode)
	// to set a password: channel operator must do command: MODE #name_of_channel +k
	Server * server = message->getServer();
	Client * client = message->getClient();
	Replies reply(*client);
	std::vector<std::string>	channels = server->msg_split(message->getParams()[0], ",");
	// if channel does not exist, create a Channel object, put it in the channel list and put client as chan op
	for (size_t i = 0; i < channels.size(); i++)
	{
		std::string chanName = channels[i].data(); // get channel name
		std::string fullMsg = ":" + client->getPrefix() + " " + message->getCMD() + " :" + chanName + "\r\n";
		if (server->_channels.find(chanName) == server->_channels.end())
		{
			std::cout << "Channel " << chanName << " does not exist" << std::endl;
			// Create channel and set first client as chan operator
			Channel mychan(chanName, client, "o");
			server->_channels[chanName] = mychan;
			std::map<Client*, std::string> mapOfClients = server->_channels[chanName].getClientsMap();
			std::cout << "Channel " << chanName << " created and added to server list. User added to channel." << std::endl;
			for (std::map<Client*, std::string>::iterator it = mapOfClients.begin(); it != mapOfClients.end(); it++)
				send(it->first->getSocket(), fullMsg.c_str(), fullMsg.size(), 0); // JOIN message from server
			send(client->getSocket(), reply.RPL_NAMREPLY(chanName, "=", "@").c_str(), reply.RPL_NAMREPLY(chanName, "=", "@").size(), 0); // list of members in the channel
			send(client->getSocket(), reply.RPL_ENDOFNAMES(chanName).c_str(), reply.RPL_ENDOFNAMES(chanName).size(), 0); // end of member list
		}
		else
		{
			std::cout << "Channel " << chanName << " already exists" << std::endl;
			server->_channels[chanName].addClient(client, "");
			std::map<Client*, std::string> mapOfClients = server->_channels[chanName].getClientsMap();
			std::cout << "User added to channel." << std::endl;
			for (std::map<Client*, std::string>::iterator it = mapOfClients.begin(); it != mapOfClients.end(); it++)
				send(it->first->getSocket(), fullMsg.c_str(), fullMsg.size(), 0); // JOIN message from server
			send(client->getSocket(), reply.RPL_NAMREPLY(chanName, "=", "@").c_str(), reply.RPL_NAMREPLY(chanName, "=", "@").size(), 0); // list of members in the channel
			send(client->getSocket(), reply.RPL_ENDOFNAMES(chanName).c_str(), reply.RPL_ENDOFNAMES(chanName).size(), 0); // end of member list
		}
	}
}

void cmd_part(Message * message)
{
	// TO DO: handle multiple channels split with ,
	// std::string chanName = message->getParams()[0]; // get channel name
	Server * server = message->getServer();
	Client * client = message->getClient();
	Replies replies(*client);
	// std::string fullMsg = ":" + client->getPrefix() + " " + message->getFullMsg() + "\r\n";
	std::vector<std::string>	channels = server->msg_split(message->getParams()[0], ",");
	if (message->getParams().size() < 1)
	{
		send(client->getSocket(), replies.ERR_NEEDMOREPARAMS(message->getCMD()).data(), replies.ERR_NEEDMOREPARAMS(message->getCMD()).size(), 0);
		return ;
	}
	for (size_t i = 0; i < channels.size(); i++)
	{
		std::string chanName = channels[i].data(); // get channel name
		std::string fullMsg = ":" + client->getPrefix() + " " + message->getCMD() + " :" + chanName + "\r\n";
		std::map<Client*, std::string>::iterator it;
		if (server->_channels.find(chanName) == server->_channels.end()) // check if channel exists
		{
			// std::cout << "Channel " << chanName << " does not exist" << std::endl;
			send(client->getSocket(), replies.ERR_NOSUCHCHANNEL(chanName).data(), replies.ERR_NOSUCHCHANNEL(chanName).size(), 0); // channel does not exist
		}
		else
		{
			std::map<Client*, std::string>& mapOfClients = server->_channels[chanName].getClientsMap();
			for (it = mapOfClients.begin(); it != mapOfClients.end(); it++)
			{
				if (client->getSocket() == it->first->getSocket()) // check if client in channel
					break;
			}
			if (it == mapOfClients.end())
			{
				send(client->getSocket(), replies.ERR_NOTONCHANNEL(chanName).data(), replies.ERR_NOTONCHANNEL(chanName).size(), 0); // channel exists but client not in it
				break;
			}
			for (std::map<Client*, std::string>::iterator it = mapOfClients.begin(); it != mapOfClients.end(); it++)
				send(it->first->getSocket(), fullMsg.c_str(), fullMsg.size(), 0); // send /PART message to all clients on channel
			server->_channels[chanName].removeClient(client); // remove client from our list of clients in channel
			// Check if channel is empty, if so, erase it
			if (mapOfClients.empty())
				server->_channels.erase(chanName);
		}
	}
}

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
		send(client->getSocket(), reply.ERR_NORECIPIENT(message->getCMD()).data(), reply.ERR_NORECIPIENT(message->getCMD()).size(), 0);
		if (DEBUG)
			std::cout << "No recipient" << std::endl;
		return ;
	}
	std::string msgtarget = message->getParams()[0];
	std::vector<std::string> targets = message->getTargets();
	std::string fullMsg = ":" + client->getPrefix() + " " + message->getFullMsg() + "\r\n";
	for (size_t i = 0; i < targets.size(); i++)
	{
		if (targets[i][0] == '#')
		{
			if (server->_channels.find(targets[i]) == server->_channels.end()) /* channel does not exist*/
			{
				Replies reply(*client);
				if (DEBUG)
					std::cout << "Unknown channel" << std::endl;
				send(client->getSocket(), reply.ERR_NOSUCHNICK(client->getNick()).data(), reply.ERR_NOSUCHNICK(client->getNick()).size(), 0);
			}
			else
			{
				std::map<Client*, std::string> mapOfClients = server->_channels[targets[i]].getClientsMap();
				for (std::map<Client*, std::string>::iterator it = mapOfClients.begin();\
					it != mapOfClients.end(); it++)
				{
					if (it->first->getSocket() != client->getSocket())
						send(it->first->getSocket(), fullMsg.c_str(), fullMsg.size(), 0);
				}
				if (DEBUG)
					std::cout << "Message sent to a channel" << std::endl;
			}
		}
		else
		{
			int targetfd = server->getFdWithNick(targets[i]);
			if (targetfd == -1)
			{
				Replies reply(*client);
				send(client->getSocket(), reply.ERR_NOSUCHNICK(client->getNick()).data(), reply.ERR_NOSUCHNICK(client->getNick()).size(), 0);
				if (DEBUG)
					std::cout << "Wrong recipient" << std::endl;
			}
			else
			{
				if (DEBUG)
					std::cout << "Message sent to a user" << std::endl;
				send(server->getFdWithNick(targets[i]), fullMsg.c_str(), fullMsg.size(), 0);
			}
		}
		return ;
	}
}

void cmd_notice(Message * message)
{
	Server * server = message->getServer();
	Client * client = message->getClient();

	if (message->getParams().size() == 0)
	{
		Replies reply(*client);
		reply.ERR_NORECIPIENT(message->getCMD());
		return ;
	}
	std::string msgtarget = message->getParams()[0];
	std::vector<std::string> targets = message->getTargets();
	std::string fullMsg = ":" + client->getPrefix() + " " + message->getFullMsg() + "\r\n";
	for (size_t i = 0; i < targets.size(); i++)
	{
		if (targets[i][0] == '#')
		{
			// TO  DO: check that channel exists
			std::cout << "Message sent to a channel" << std::endl;
			std::map<Client*, std::string> mapOfClients = server->_channels[targets[i]].getClientsMap();
			for (std::map<Client*, std::string>::iterator it = mapOfClients.begin();
				it != mapOfClients.end(); it++)
			{
				if (it->first->getSocket() != client->getSocket())
				{
					std::cout << "This client is in the chan: " << it->first->getSocket() <<std::endl;
					std::cout << "This message is being sent: " << fullMsg << " to client " << it->first->getSocket() << std::endl;
					send(it->first->getSocket(), fullMsg.c_str(), fullMsg.size(), 0);
				}
			}
		}
		else
		{
			// TO DO: check that user exists
			std::cout << "Message sent to a user" << std::endl;
			send(server->getFdWithNick(targets[i]), fullMsg.c_str(), fullMsg.size(), 0);
		}
	}
}

void    cmd_oper(Message * message) {

    Client * client = message->getClient();
    Replies replies(*client);

	if (message->getParams().size() < 2) // check if both <name> and <password> are entered
        send(client->getSocket(), replies.ERR_NEEDMOREPARAMS("OPER").data(), replies.ERR_NEEDMOREPARAMS("OPER").size(), 0);
    else if (message->getParams()[0] == "operator" && message->getParams()[1] == "password") // checks if <name> is set as "operator" and <password> as "password"
    {
        send(client->getSocket(), replies.RPL_YOUREOPER().data(), replies.RPL_YOUREOPER().size(), 0);
        client->setIRCMode("wio"); // sets client's privileged to operator
        replies.setVariables(*client); // updates client's new info
        send(client->getSocket(), replies.RPL_UMODEIS().data(), replies.RPL_UMODEIS().size(), 0); // displays new privileges
    }
    else
        send(client->getSocket(), replies.ERR_PASSWDMISMATCH().data(), replies.ERR_PASSWDMISMATCH().size(), 0); // wrong password
}

void    cmd_wallops(Message * message) {

    Client	*client = message->getClient();
	Server	*server = message->getServer();
    Replies replies(*client);

	std::string wallop = ":" + client->getPrefix() + " WALLOPS " + message->getParams()[0] + "\r\n";
    if (client->getIRCMode().find("o") == std::string::npos) // check if user has IRC operator privileges
        send(client->getSocket(), replies.ERR_NOPRIVILEGES("Permission Denied- You're not an IRC operator").data(), replies.ERR_NOPRIVILEGES("Permission Denied- You're not an IRC operator").size(), 0);
	else
	{
		for (size_t i = 0; i < server->getClients().size(); i++)
		{
			if (server->getClients()[i].getIRCMode().find("w") != std::string::npos) // check if client has "w" mode
				send(server->getClients()[i].getSocket(), wallop.data(), wallop.size(), 0); // sends message to all clients with "w" mode including the sender
		}
	}
}

void    cmd_kill(Message * message) {

    Client	*client = message->getClient();
	Server	*server = message->getServer();
    Replies	replies(*client);
	size_t	i = 2;
	bool	nick = false;

	std::string	full_params = message->getParams()[1];

	while (i < message->getParams().size())
	{
		full_params = full_params + " " + message->getParams()[i]; // get all the params in one string
		i++;
	}

	i = 0;

	std::string kill = ":" + client->getPrefix() + " KILL " + full_params + "\r\n";
	std::string quit = ":" + client->getPrefix() + " QUIT " + full_params + "\r\n";

	if (message->getParams().size() < 3 && message->getParams()[1] == ":") // check if both <name> and <reason> are entered
        send(client->getSocket(), replies.ERR_NEEDMOREPARAMS("KILL").data(), replies.ERR_NEEDMOREPARAMS("KILL").size(), 0);
	else if (client->getIRCMode().find("o") == std::string::npos) // check if client has the IRC operator privilege
		send(client->getSocket(), replies.ERR_NOPRIVILEGES("Permission Denied- You're not an IRC operator").data(), replies.ERR_NOPRIVILEGES("Permission Denied- You're not an IRC operator").size(), 0);
	else
	{
		while (i < server->getClients().size())
		{
			if (server->getClients()[i].getNick() == message->getParams()[0])
			{
				send(server->getClients()[i].getSocket(), kill.data(), kill.size(), 0); // send /KILL message to target client
				send(server->getClients()[i].getSocket(), quit.data(), quit.size(), 0); // send /QUIT message to target client
				std::cout << "pollserver: socket " << server->getClients()[i].getSocket() << " hung up" << std::endl;
				close(server->getClients()[i].getSocket()); // close target client fd
				server->getClients().erase(server->getClients()[i].getSocket()); // erase client from our list
				nick = true;
				break;
			}
			i++;
		}
		if (nick == false)
			send(client->getSocket(), replies.ERR_NOSUCHNICK(client->getNick()).data(), replies.ERR_NOSUCHNICK(client->getNick()).size(), 0);
	}
}

void	cmd_whois(Message * message)
{
	Server * server = message->getServer();
	Client * client = message->getClient();

	if (message->getParams().size() == 0)
	{
		// TO DO: ERR_NO_RECIPIENT to handle
		return ;
	}
	else
	{
		std::string msgtarget = message->getParams()[0];
		std::vector<std::string> targets = message->getTargets();
		for (size_t i = 0; i < targets.size(); i++)
		{
			if (targets[i][0] == '#')
				continue;
			else
			{
				try
				{
					Client targetclient = server->getClientWithNick(targets[i]);
					Replies reply(targetclient);
					send(client->getSocket(), reply.RPL_WHOISUSER().data(), reply.RPL_WHOISUSER().size(), 0);
				}
				catch(const std::exception& e)
				{
					Replies reply(*client);
					send(client->getSocket(), reply.ERR_NOSUCHNICK(client->getNick()).data(), reply.ERR_NOSUCHNICK(client->getNick()).size(), 0);
				}
			}
		}
		return ;
	}
}

void    cmd_kick(Message * message) {
// TO DO: if client is IRC operator, should be able to kick any clients (to be checked)
	std::string chanName = message->getParams()[0];
	std::string targetName = message->getParams()[1];
	Server * server = message->getServer();
	Client * client = message->getClient();
	Replies replies(*client);
	std::string fullMsg = ":" + client->getPrefix() + " " + message->getFullMsg() + "\r\n";
	std::string msgtarget = message->getParams()[0];
	std::map<Client*, std::string> mapOfClients = server->_channels[chanName].getClientsMap();
	if (server->_channels.find(chanName) == server->_channels.end()) // check if channel exists
		send(client->getSocket(), replies.ERR_NOSUCHCHANNEL(chanName).data(), replies.ERR_NOSUCHCHANNEL(chanName).size(), 0);
	else if (mapOfClients[client].find("o") == std::string::npos) // check if client has channel operator privilege
		send(client->getSocket(), replies.ERR_CHANOPRIVSNEEDED(chanName).data(), replies.ERR_CHANOPRIVSNEEDED(chanName).size(), 0);
	else
	{
		std::map<Client*, std::string> mapOfClients = server->_channels[msgtarget].getClientsMap();
		std::map<Client*, std::string>::iterator it;
		for (it = mapOfClients.begin(); it != mapOfClients.end(); it++)
		{
			if (targetName == it->first->getNick()) // check if target client is in channel
				break;
		}
		if (it == mapOfClients.end()) // if target client is not in channel
		{
			chanName += " ";
			chanName += targetName;
			send(client->getSocket(), replies.ERR_USERNOTINCHANNEL(chanName).data(), replies.ERR_USERNOTINCHANNEL(chanName).size(), 0);
			return ;
		}
		for (std::map<Client*, std::string>::iterator it = mapOfClients.begin(); it != mapOfClients.end(); it++)
			send(it->first->getSocket(), fullMsg.c_str(), fullMsg.size(), 0);
		server->_channels[chanName].removeClient(it->first); // remove target client from our list
		// std::cout << "User removed from channel." << std::endl;
	}
}

void    cmd_invite(Message * message) {

	std::string chanName = message->getParams()[1];
	std::string targetName = message->getParams()[0];
	Server * server = message->getServer();
	Client * client = message->getClient();
	Replies replies(*client);
	std::string fullMsg = ":" + client->getPrefix() + " " + message->getFullMsg() + "\r\n";
	if (server->_channels.find(chanName) != server->_channels.end()) // check if channel exists
	{
		// std::cout << "Channel " << chanName << " does not exist" << std::endl;
		std::map<Client*, std::string> mapOfClients = server->_channels[chanName].getClientsMap();
		std::map<Client*, std::string>::iterator it;
		for (it = mapOfClients.begin(); it != mapOfClients.end(); it++)
		{
			if (targetName == it->first->getNick()) // check if client is in channel in order to invite
				break;
		}
		if (it == mapOfClients.end())
		{
			send(client->getSocket(), replies.ERR_NOTONCHANNEL(chanName).data(), replies.ERR_NOTONCHANNEL(chanName).size(), 0); // channel exists but client inviting not in it
			return ;
		}
	}
	size_t i = 0;
	while (i < server->getClients().size())
	{
		if (targetName == server->getClients()[i].getNick())
			break;
		i++;
	}
	if (i == server->getClients().size())
		send(client->getSocket(), replies.ERR_NOSUCHNICK(targetName).data(), replies.ERR_NOSUCHNICK(targetName).size(), 0); // check if target client exists
	else
	{
		send(client->getSocket(), replies.RPL_INVITING(targetName, chanName).data(), replies.RPL_INVITING(targetName, chanName).size(), 0); // send RPL to client inviting
		send(server->getClients()[i].getSocket(), fullMsg.data(), fullMsg.size(), 0); // send /INVITE msg to target client
	}
}

void		cmd_mode(Message * message)
{
	(void)message;
}

/* ************************************************************************** */