/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchate <gduchate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:43:49 by rliu              #+#    #+#             */
/*   Updated: 2023/04/21 11:35:31 by gduchate         ###   ########.fr       */
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
	_cmdMap["PING"] = &cmd_ping;
	_cmdMap["PASS"] = &cmd_pass; /*Ran*/
	_cmdMap["NICK"] = &cmd_nick; /*Ran*/
	_cmdMap["USER"] = &cmd_user; /*Ran*/
	_cmdMap["JOIN"] = &cmd_join; /*Aristide*/
	_cmdMap["PRIVMSG"] = &cmd_privmsg; /*Guillemette*/
	_cmdMap["PART"] = &cmd_part; /*Guillemette*/
	_cmdMap["OPER"] = &cmd_oper; /*Aristide*/
	_cmdMap["WALLOPS"] = &cmd_wallops;/*Aristide*/
	_cmdMap["KILL"] = &cmd_kill;/*Aristide*/
	_cmdMap["KICK"] = &cmd_kick; /*Aristide*/
	_cmdMap["NOTICE"] = &cmd_notice; /*Guillemette*/
	_cmdMap["WHOIS"] = &cmd_whois; /*Guillemette*/
	_cmdMap["INVITE"] = &cmd_invite; /*Aristide*/
	// _cmdMap["MODE"] = &cmd_mode; /*Guillemette*/
	_cmdMap["QUIT"] = &cmd_quit; /*Ran*/
	// Ctrl C signal handling Aristide/Ran
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
** --------------------------------- COMMANDS ---------------------------------
*/

void cmd_pass(Message * message)
{
	Server * server = message->getServer();
	Client * client = message->getClient();
	Replies reply(*client);
	std::string rplErr;
	if (client->getPassStatus()){
		rplErr=reply.ERR_ALREADYREGISTRED("PASS");
		send(client->getSocket(),rplErr.c_str(), rplErr.size(), 0);
	}
	else if (message->getParams().size() < 1 || message->getParams().empty()){
		std::string rplErr = reply.ERR_NEEDMOREPARAMS("PASS");
		send(client->getSocket(),rplErr.c_str(), rplErr.size(), 0);
	}
	else if (server->getPassword() != message->getParams()[0]){
		if (DEBUG)
			std::cout << "password is wrong" << std::endl;
		std::string rplErr = reply.ERR_PASSWDMISMATCH();
		send(client->getSocket(),rplErr.c_str(), rplErr.size(), 0);
	}
	else{
		message->getClient()->setPass( message->getParams()[0]);
		client->setPassRegistered();
	}
}

void cmd_nick(Message * message)
{
	Server * server = message->getServer();
	Client * client = message->getClient();
	Replies reply(*client);
	std::string rplErr;
	if (message->getParams().size()< 1 || message->getParams()[0].empty())
	{
		rplErr = reply.ERR_NONICKNAMEGIVEN();
		send(client->getSocket(),rplErr.c_str(), rplErr.size(), 0);
		return;
	}
	else{
		std::string nick = message->getParams()[0];
		if (nick.size() > 9){
			nick.resize(9);
			std::cout << "NICK : " << nick << std::endl;
		}
		//ERRONEUSNICKNAME
		for (size_t i = 0; i < nick.size(); i++)
		{
			if (isdigit(nick[0]) || !isprint(nick[i])){
				rplErr = reply.ERR_ERRONEUSNICKNAME(nick, "Erroneous nickname");
				send(client->getSocket(),rplErr.c_str(), rplErr.size(), 0);
				return;
			}
		}
		std::map<int, Client>::iterator     it;
		for (it = server->getClients().begin(); it != server->getClients().end(); it++)
		{
			if (it->first == client->getSocket()) // don't send message to client's own fd
				continue ;
			if (nick == it->second.getNick()){
				std::string rplNickInUse;
				rplNickInUse = reply.ERR_NICKNAMEINUSE(nick, "this nickname is in use!");
				send(client->getSocket(),rplNickInUse.c_str(), rplNickInUse.size(), 0);
				return;
			}
		}
		client->setNick(nick);
		client->setNickRegistered();
		if (client->getRegistrationStatus())
		{
			std::string msg = ":" + client->getPrefix() + " NICK " + nick + "\r\n";
			send(client->getSocket(), msg.c_str(), msg.size(), 0);
			client->setPrefix();
		}

	}
}

void cmd_user(Message * message)
{
	Client * client = message->getClient();
	Replies reply(*client);
	std::string rplErr;
	if (client->getUsrStatus()){
		rplErr = reply.ERR_ALREADYREGISTRED("USER is already registered");
		std::cout << "test usr" << message->getFullMsg() << std::endl;
		send(client->getSocket(),rplErr.c_str(), rplErr.size(), 0);
		return;
	 }
	if (message->getParams().size()< 4 || message->getParams()[0].empty())
	{
		rplErr = reply.ERR_NEEDMOREPARAMS("USER");
		send(client->getSocket(),rplErr.c_str(), rplErr.size(), 0);
		return;
	}
	else
	{
		client->setUsr(message->getParams()[0]);
		client->setHostname(message->getParams()[1]);
		client->setServername(message->getParams()[2]);
		if (message->getParams()[3][0] == ':')
		{
			std::string realName(message->getParams()[3], 1, message->getParams()[3].size()-1);
			for (size_t i = 4; i < message->getParams().size(); i++)
				realName += " " + message->getParams()[i];
			client->setRealname(realName);
		}
		else
		{	
			std::string realName = message->getParams()[3];
			client->setRealname(realName);
		}
		client->setUsrRegistered();
	 }
}

void cmd_ping(Message * message)
{
	// As a result of server correctly responding "PONG", the irssi client interface does not
	// show [LAG] message anymore
	if (message->getClient()->getSocket() < 4)
		return;
	if (DEBUG)
		std::cout << "[Server] sending PONG to client (" <<message->getClient()->getSocket() << ")" << std::endl;
	if (message->getParams().size() < 1)
	{
		Client * client = message->getClient();
		Replies reply(*client);
		send(client->getSocket(), reply.ERR_NEEDMOREPARAMS(message->getCMD()).data(), reply.ERR_NEEDMOREPARAMS(message->getCMD()).size(), 0);
		return ;
	}
	std::string answer = "PONG " + message->getParams()[0] + "\r\n";
	send(message->getClient()->getSocket(), answer.c_str(), answer.size(), 0);
}

std::string const				Channel::getStringOfMembers()
{
	std::string result = "";
	for (std::map<Client*, std::string>::iterator it = _clientsMap.begin(); it != _clientsMap.end(); it++)
	{
		std::string nick = it->first->getNick();
		if (it->second.find('o') != std::string::npos)
			nick = "@" + nick;
		if (result != "")
			result += " " + nick;
		else
			result = nick;
	}
	return (result);
}

void cmd_join(Message * message)
{
	// TO DO: handle channel password
	// User must provide a password if channel is key protected (k mode)
	// to set a password: channel operator must do command: MODE #name_of_channel +k
	Server * server = message->getServer();
	Client * client = message->getClient();
	Replies reply(*client);
	if (message->getParams().size() < 1)
	{
		send(client->getSocket(), reply.ERR_NEEDMOREPARAMS(message->getCMD()).data(), reply.ERR_NEEDMOREPARAMS(message->getCMD()).size(), 0);
		return ;
	}
	std::vector<std::string>	channels = server->msg_split(message->getParams()[0], ",");
	// if channel does not exist, create a Channel object, put it in the channel list and put client as chan op
	for (size_t i = 0; i < channels.size(); i++)
	{
		std::string chanName = channels[i].data(); // get channel name
		if (chanName[0] != '#')
		{
			send(client->getSocket(), reply.ERR_BADCHANMASK(chanName).data(), reply.ERR_BADCHANMASK(chanName).size(), 0);
			break;
		}
		std::string fullMsg = ":" + client->getPrefix() + " " + message->getCMD() + " :" + chanName + "\r\n";
		if (server->_channels.find(chanName) == server->_channels.end())
		{
			std::cout << "Channel " << chanName << " does not exist" << std::endl;
			// Create channel and set first client as chan operator
			Channel mychan(chanName, client, "o");
			server->_channels[chanName] = mychan;
			Channel *channel = &server->_channels[chanName];
			std::map<Client*, std::string> mapOfClients = channel->getClientsMap();
			std::cout << "Channel " << chanName << " created and added to server list. User added to channel." << std::endl;
			if (DEBUG)
				std::cout << "String of members: " << channel->getStringOfMembers() << std::endl;
			send(client->getSocket(), reply.RPL_NAMREPLY("=", chanName, channel->getStringOfMembers()).data(), reply.RPL_NAMREPLY(chanName, "=", channel->getStringOfMembers()).size(), 0); // list of members in the channel
			send(client->getSocket(), reply.RPL_ENDOFNAMES(chanName).data(), reply.RPL_ENDOFNAMES(chanName).size(), 0); // end of member list
			send(client->getSocket(), fullMsg.data(), fullMsg.size(), 0); // JOIN message from server
		}
		else
		{
			std::cout << "Channel " << chanName << " already exists" << std::endl;
			Channel *channel = &server->_channels[chanName];
			channel->addClient(client, "");
			std::cout << "User " << client->getNick() << " added to channel." << std::endl;
			std::map<Client*, std::string> mapOfClients = channel->getClientsMap();
			if (DEBUG)
				std::cout << "String of members: " << channel->getStringOfMembers() << std::endl;
			send(client->getSocket(), reply.RPL_NAMREPLY("=", chanName, channel->getStringOfMembers()).data(), reply.RPL_NAMREPLY(chanName, "=", channel->getStringOfMembers()).size(), 0); // list of members in the channel
			send(client->getSocket(), reply.RPL_ENDOFNAMES(chanName).data(), reply.RPL_ENDOFNAMES(chanName).size(), 0); // end of member list
			for (std::map<Client*, std::string>::iterator it = mapOfClients.begin(); it != mapOfClients.end(); it++)
				send(it->first->getSocket(), fullMsg.data(), fullMsg.size(), 0); // JOIN message from server
		}
	}
}

void cmd_part(Message * message)
{
	Server * server = message->getServer();
	Client * client = message->getClient();
	Replies replies(*client);
	if (message->getParams().size() < 1)
	{
		send(client->getSocket(), replies.ERR_NEEDMOREPARAMS(message->getCMD()).data(), replies.ERR_NEEDMOREPARAMS(message->getCMD()).size(), 0);
		return ;
	}
	std::vector<std::string>	channels = server->msg_split(message->getParams()[0], ",");
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
		if (targets[i] == "#bot")
			botReply(message);
		else if (targets[i][0] == '#')
		{
			if (server->_channels.find(targets[i]) == server->_channels.end()) /* channel does not exist*/
			{
				Replies reply(*client);
				if (DEBUG)
					std::cout << "Unknown channel" << std::endl;
				send(client->getSocket(), reply.ERR_NOSUCHNICK(targets[i]).data(), reply.ERR_NOSUCHNICK(targets[i]).size(), 0);
			}
			else
			{
				std::map<Client*, std::string> mapOfClients = server->_channels[targets[i]].getClientsMap();
				for (std::map<Client*, std::string>::iterator it = mapOfClients.begin();\
					it != mapOfClients.end(); it++)
				{
					if (it->first->getSocket() != client->getSocket())
						send(it->first->getSocket(), fullMsg.data(), fullMsg.size(), 0);
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
				send(client->getSocket(), reply.ERR_NOSUCHNICK(targets[i]).data(), reply.ERR_NOSUCHNICK(targets[i]).size(), 0);
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

void	cmd_notice(Message * message)
{
	Server * server = message->getServer();
	Client * client = message->getClient();

	if (message->getParams().size() < 1)
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
			if (server->_channels.find(targets[i]) == server->_channels.end()) /* channel does not exist*/
			{
				Replies reply(*client);
				if (DEBUG)
					std::cout << "Unknown channel" << std::endl;
				send(client->getSocket(), reply.ERR_NOSUCHNICK(targets[i]).data(), reply.ERR_NOSUCHNICK(targets[i]).size(), 0);
			}
			else
			{
				std::map<Client*, std::string> mapOfClients = server->_channels[targets[i]].getClientsMap();
				for (std::map<Client*, std::string>::iterator it = mapOfClients.begin(); it != mapOfClients.end(); it++)
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
				send(client->getSocket(), reply.ERR_NOSUCHNICK(targets[i]).data(), reply.ERR_NOSUCHNICK(targets[i]).size(), 0);
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
	}
}

void	cmd_oper(Message * message) {

	Client * client = message->getClient();
	Replies replies(*client);

	if (message->getParams().size() < 2) // check if both <name> and <password> are entered
		send(client->getSocket(), replies.ERR_NEEDMOREPARAMS("OPER").data(), replies.ERR_NEEDMOREPARAMS("OPER").size(), 0);
	else if (message->getParams()[0] == "operator" && message->getParams()[1] == "password") // checks if <name> is set as "operator" and <password> as "password"
	{
		send(client->getSocket(), replies.RPL_YOUREOPER().data(), replies.RPL_YOUREOPER().size(), 0);
		client->setIRCMode("o"); // sets client's privileges to operator
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

	if (message->getParams().size() < 2)
    {
		send(client->getSocket(), replies.ERR_NEEDMOREPARAMS("WALLOPS").data(), replies.ERR_NEEDMOREPARAMS("WALLOPS").size(), 0);
		return ;
	}
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

	if (message->getParams().size() < 2 || (message->getParams().size() == 2 && message->getParams()[1] == ":"))  // check if both <name> and <reason> are entered
		send(client->getSocket(), replies.ERR_NEEDMOREPARAMS("KILL").data(), replies.ERR_NEEDMOREPARAMS("KILL").size(), 0);
	else if (client->getIRCMode().find("o") == std::string::npos) // check if client has the IRC operator privilege
		send(client->getSocket(), replies.ERR_NOPRIVILEGES("Permission Denied- You're not an IRC operator").data(), replies.ERR_NOPRIVILEGES("Permission Denied- You're not an IRC operator").size(), 0);
	else
	{
		std::string	full_params = message->getParams()[1];

		while (i < message->getParams().size())
		{
			full_params = full_params + " " + message->getParams()[i]; // get all the params in one string
			i++;
		}

		i = 0;

		std::string kill = ":" + client->getPrefix() + " KILL " + full_params + "\r\n";
		while (i < server->getClients().size())
		{
			if (server->getClients()[i].getNick() == message->getParams()[0])
			{
				std::string quit = ":" + server->getClients()[i].getPrefix() + " QUIT " + full_params + "\r\n";
				send(server->getClients()[i].getSocket(), kill.data(), kill.size(), 0); // send /KILL message to target client
				send(server->getClients()[i].getSocket(), quit.data(), quit.size(), 0); // send /QUIT message to target client
				std::cout << "pollserver: socket " << server->getClients()[i].getSocket() << " hung up" << std::endl;
				// close(server->getClients()[i].getSocket()); // close target client fd
				// server->getClients().erase(server->getClients()[i].getSocket()); // erase client from our list
				int sfd = server->getClients()[i].getSocket();
				close(sfd);
				for (size_t i = 0; i < server->_pollfds.size(); i++)
					if(server->_pollfds[i].fd == sfd)
						server->_pollfds.erase(server->_pollfds.begin() + i);
				// std::cout << "Client " << client->getNick() << "(" << sfd  << ") "  << msg + "\n";
				if (server->getClients().find(sfd) != server->getClients().end() )
					server->getClients().erase(sfd);
				nick = true;
				break;
			}
			i++;
		}
		if (nick == false)
			send(client->getSocket(), replies.ERR_NOSUCHNICK(message->getParams()[0]).data(), replies.ERR_NOSUCHNICK(message->getParams()[0]).size(), 0);
	}
}

void	cmd_whois(Message * message)
{
	Server * server = message->getServer();
	Client * client = message->getClient();

	if (message->getParams().size() < 1)
	{
		Replies reply(*client);
		send(client->getSocket(), reply.ERR_NONICKNAMEGIVEN().data(), reply.ERR_NONICKNAMEGIVEN().size(), 0);
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
					Replies reply(*client);
					if (DEBUG)
						std::cout << reply.RPL_WHOISUSER(targetclient.getNick(), targetclient.getUser(), targetclient.getHostName(), targetclient.getRealName()).data() << std::endl;
					send(client->getSocket(), reply.RPL_WHOISUSER(targetclient.getNick(), targetclient.getUser(), targetclient.getHostName(), targetclient.getRealName()).data(), reply.RPL_WHOISUSER(targetclient.getNick(), targetclient.getUser(), targetclient.getHostName(), targetclient.getRealName()).size(), 0);
					send(client->getSocket(), reply.RPL_ENDOFWHOIS().data(), reply.RPL_ENDOFWHOIS().size(), 0);
				}
				catch(const std::exception& e)
				{
					Replies reply(*client);
					send(client->getSocket(), reply.ERR_NOSUCHNICK(targets[i]).data(), reply.ERR_NOSUCHNICK(targets[i]).size(), 0);
				}
			}
		}
		return ;
	}
}

void	cmd_kick(Message * message) {

	Server * server = message->getServer();
	Client * client = message->getClient();
	Replies replies(*client);

	if (message->getParams().size() < 2)
    {
		send(client->getSocket(), replies.ERR_NEEDMOREPARAMS("KICK").data(), replies.ERR_NEEDMOREPARAMS("KICK").size(), 0);
		return ;
	}
	std::vector<std::string>	channelsToKick = server->msg_split(message->getParams()[0], ",");
	std::vector<std::string>	clientsToKick = server->msg_split(message->getParams()[1], ",");
	std::map<Client*, std::string>::iterator it;
	for (size_t i = 0; i < channelsToKick.size(); i++)
	{
		std::string chanName = channelsToKick[i].data(); // get channel name
		if (server->_channels.find(chanName) == server->_channels.end()) // check if channel exists
		{
			send(client->getSocket(), replies.ERR_NOSUCHCHANNEL(chanName).data(), replies.ERR_NOSUCHCHANNEL(chanName).size(), 0);
			continue;
		}
		std::map<Client*, std::string> mapOfClients = server->_channels[chanName].getClientsMap();
		if (mapOfClients[client].find("o") == std::string::npos) // check if client has channel operator privilege
		{
			send(client->getSocket(), replies.ERR_CHANOPRIVSNEEDED(chanName).data(), replies.ERR_CHANOPRIVSNEEDED(chanName).size(), 0);
			continue;
		}
		for (size_t j = 0; j < clientsToKick.size(); j++)
		{
			std::string targetName = clientsToKick[j].data();
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
				continue;
			}
			std::string fullMsg;
			if (message->getParams().size() > 2)
				fullMsg = ":" + client->getPrefix() + " " + message->getCMD() + " " + chanName + " " + targetName + " " + message->getParams()[2] + "\r\n";
			else
				fullMsg = ":" + client->getPrefix() + " " + message->getCMD() + " " + chanName + " " + targetName + "\r\n";
			for (std::map<Client*, std::string>::iterator it = mapOfClients.begin(); it != mapOfClients.end(); it++)
				send(it->first->getSocket(), fullMsg.c_str(), fullMsg.size(), 0);
			server->_channels[chanName].removeClient(it->first); // remove target client from our list
			// std::cout << "User removed from channel." << std::endl;
		}
	}
}

void	cmd_invite(Message * message) {

	Client * client = message->getClient();
	Server * server = message->getServer();
	Replies replies(*client);
	if (message->getParams().size() < 2)
    {
		send(client->getSocket(), replies.ERR_NEEDMOREPARAMS("INVITE").data(), replies.ERR_NEEDMOREPARAMS("INVITE").size(), 0);
		return ;
	}
	std::string chanName = message->getParams()[1];
	std::string targetName = message->getParams()[0];
	std::string fullMsg = ":" + client->getPrefix() + " " + message->getFullMsg() + "\r\n";
	if (server->_channels.find(chanName) != server->_channels.end()) // check if channel exists
	{
		std::map<Client*, std::string> mapOfClients = server->_channels[chanName].getClientsMap();
		std::map<Client*, std::string>::iterator it;
		for (it = mapOfClients.begin(); it != mapOfClients.end(); it++)
		{
			if (client->getNick() == it->first->getNick()) // check if client is in channel in order to invite
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

void		changeChanMode(modes & reqmode, Client * client, Channel * channel, std::vector<std::string> msg_params)
{
	std::string change = "";
	std::string currentmode = channel->getMode();
	std::cout << "currentmode: " << currentmode << std::endl;
	std::map<Client*, std::string> mapOfClients = channel->getClientsMap();
	std::map<Client*, std::string>::iterator it;
	if (reqmode.sign == '+')
	{
		for (size_t i = 0; i < reqmode.match.size(); i++)
		{
			// How to handle missing username for o
			if (currentmode.find(reqmode.match[i]) == std::string::npos && reqmode.match[i] != 'o')
				change.push_back(reqmode.match[i]);
			else if (currentmode.find(reqmode.match[i]) == std::string::npos && reqmode.match[i] == 'o' && msg_params.size() > 2) /*if o option, check that nickname is in chan*/
			{
				// TO DO: check what happens if given nick is user's nick
				for (it = mapOfClients.begin(); it != mapOfClients.end(); it++)
				{
					if (msg_params[2] == it->first->getNick())
					{
						channel->addModeArguments(msg_params[2]);
						break;
					}
				}
				if (it != mapOfClients.end()) // if target client is in channel
					change.push_back(reqmode.match[i]);
			}
		}
	}
	else
	{
		for (size_t i = 0; i < reqmode.match.size(); i++)
		{
			if (currentmode.find(reqmode.match[i]) != std::string::npos && reqmode.match[i] != 'o')
				change.push_back(reqmode.match[i]);
			else if (currentmode.find(reqmode.match[i]) != std::string::npos && reqmode.match[i] == 'o' && msg_params.size() > 2)
			{
				// TO DO: check what happens if given nick is user's nick
				for (it = mapOfClients.begin(); it != mapOfClients.end(); it++)
				{
					if (msg_params[2] == it->first->getNick())
						break;
				}
				if (it != mapOfClients.end()) // if target client is in channel
					change.push_back(reqmode.match[i]);
			}
		}
	}
	if (change != "")
	{
		std::string fullMsg = ":" + client->getPrefix() + " " + "MODE " + channel->getName() + " " + reqmode.sign + change + " \r\n";
		// Echo change to all clients in channel
		std::cout << "fullMsg sent: " << fullMsg << std::endl;
		for (it = mapOfClients.begin(); it != mapOfClients.end(); it++)
		{
			std::cout << "sent" << std::endl;
			send(it->first->getSocket(), fullMsg.data(), fullMsg.size(), 0);
		}
		if (reqmode.sign == '+')
			channel->setMode(currentmode + change);
		else
		{
			for (size_t i = 0; i < change.size(); i++)
				currentmode.erase(remove(currentmode.begin(), currentmode.end(), change[i]), currentmode.end());
			channel->setMode(currentmode);
		}
		if (DEBUG)
			std::cout << "New Chan mode: " << channel->getMode() << std::endl;
	}
}

void		changeIRCMode(modes & reqmode, Client * client)
{
	std::string change = "";
	std::string currentmode = client->getIRCMode();
	if (reqmode.sign == '+')
	{
		for (size_t i = 0; i < reqmode.match.size(); i++)
		{
			if (currentmode.find(reqmode.match[i]) == std::string::npos && reqmode.match[i] != 'o')
				change.push_back(reqmode.match[i]);
		}
	}
	else
	{
		for (size_t i = 0; i < reqmode.match.size(); i++)
		{
			if (currentmode.find(reqmode.match[i]) != std::string::npos)
				change.push_back(reqmode.match[i]);
		}
	}
	if (change != "")
	{
		std::string fullMsg = ":" + client->getPrefix() + " " + "MODE " + client->getNick() + " " + reqmode.sign + change + "\r\n";
		send(client->getSocket(), fullMsg.c_str(), fullMsg.size(), 0);
		if (reqmode.sign == '+')
			client->setIRCMode(currentmode + change);
		else
		{
			for (size_t i = 0; i < change.size(); i++)
				currentmode.erase(remove(currentmode.begin(), currentmode.end(), change[i]), currentmode.end());
			client->setIRCMode(currentmode);
		}
		if (DEBUG)
			std::cout << "New IRC mode: " << client->getIRCMode() << std::endl;
	}
}

void		setModesAttributes(modes & reqmode, std::string raw, std::string flags)
{
	if (raw == "")
		return;
	if (raw[0] == '-' || raw[0] == '+')
	{
		reqmode.sign = 	raw[0];
		reqmode.raw = raw.substr(1);
	}
	else
	{
		reqmode.sign = '+';
		reqmode.raw = raw;
	}
	std::string match = "";
	for (size_t i = 0; i < reqmode.raw.size(); i++)
	{
		if (flags.find(reqmode.raw[i]) != std::string::npos && match.find(reqmode.raw[i]) == std::string::npos)
			match.push_back(reqmode.raw[i]);
		else if (flags.find(reqmode.raw[i]) == std::string::npos)
			reqmode.ret.push_back(reqmode.raw[i]);
	}
	reqmode.match = match;
	if (DEBUG)
		std::cout << "Match: " << reqmode.match << " and sign: " << reqmode.sign << " and ret: " << reqmode.ret << std::endl;
}

void		cmd_mode(Message * message)
{
	Server * server = message->getServer();
	Client * client = message->getClient();
	Replies reply(*client);

	if (message->getParams().size() == 0)
	{
		send(client->getSocket(), reply.ERR_NEEDMOREPARAMS("MODE").data(), reply.ERR_NEEDMOREPARAMS("MODE").size(), 0);
		return ;
	}
	std::string msgtarget = message->getParams()[0];
	// Channel modes
	if (msgtarget[0] == '#')
	{
		// Cannot find the channel
		if (server->_channels.find(msgtarget) == server->_channels.end())
		{
			send(client->getSocket(), reply.ERR_NOSUCHCHANNEL(msgtarget).data(), reply.ERR_NOSUCHCHANNEL(msgtarget).size(), 0);
			return ;
		}
		Channel * channel = &server->_channels[msgtarget];
		// Channel found w/o other params >> for info only
		if (message->getParams().size() == 1)
		{
			if (DEBUG)
				std::cout << reply.RPL_CHANNELMODEIS(channel->getName(), channel->getMode(), channel->getModeArguments()).data() << std::endl;
			send(client->getSocket(), reply.RPL_CHANNELMODEIS(channel->getName(), channel->getMode(), channel->getModeArguments()).data(), reply.RPL_CHANNELMODEIS(channel->getName(), channel->getMode(), "params").size(), 0);
			return ;
		}
		// Not a channel operator of the channel
		std::map<Client*, std::string> mapOfClients = server->_channels[msgtarget].getClientsMap();
		if (mapOfClients[client].find('o') == std::string::npos)
		{
			send(client->getSocket(), reply.ERR_CHANOPRIVSNEEDED(msgtarget).data(), reply.ERR_CHANOPRIVSNEEDED(msgtarget).size(), 0);
			return ;
		}
		// Parse mode
		modes reqmode;
		setModesAttributes(reqmode, message->getParams()[1], CHANMODEFLAGS);
		changeChanMode(reqmode, client, channel, message->getParams());
	}
	else
	// User modes
	{
		if (msgtarget != client->getNick()) /* error- Can't change mode for other users */
		{
			send(client->getSocket(), reply.ERR_USERSDONTMATCH().data(), reply.ERR_USERSDONTMATCH().size(), 0);
			return ;
		}
		else if (message->getParams().size() == 1) /* display user mode*/
		{
			send(client->getSocket(), reply.RPL_UMODEIS().data(), reply.RPL_UMODEIS().size(), 0);
			return ;
		}
		else /* change user mode*/
		{
			modes reqmode;
			setModesAttributes(reqmode, message->getParams()[1], USERMODEFLAGS);
			changeIRCMode(reqmode, client);
			if (reqmode.ret != "")
			{
				Replies reply(*client);
				send(client->getSocket(), reply.ERR_UNKNOWNMODE().data(), reply.ERR_UNKNOWNMODE().size(), 0);
			}
			return ;
		}
	}

//    The MODE command is provided so that user chan change their own mode
//    i - marks a user as invisible;
//    s - marks a user for receipt of server notices;
//    w - user receives wallops;
//    o - operator flag.


//    The MODE command is provided so that channel operators may change the
//    characteristics of `their' channel.  It is also required that servers
//    be able to change channel modes so that channel operators may be
//    created.

//    The various modes available for channels are as follows:

//  o - give/take channel operator privileges;
//  (not handled) - private channel flag;
//  (not handled) - secret channel flag;
//  i - invite-only channel flag;
//  t - topic settable by channel operator only flag;
//  n - no messages to channel from clients on the outside;
//  (not handled) - moderated channel;
//  (not handled) l - set the user limit to channel;
//  (not handled) b - set a ban mask to keep users out;
//  (not handled) v - give/take the ability to speak on a moderated channel;
//  (not handled) k - set a channel key (password).
}

void cmd_quit(Message *message) {

	Client *client = message->getClient();
	Server *server = message->getServer();
	std::string msg = message->getFullMsg();
	int sfd = client->getSocket();
	close(sfd);
	for (size_t i = 0; i < server->_pollfds.size(); i++)
		if(server->_pollfds[i].fd == sfd)
			server->_pollfds.erase(server->_pollfds.begin() + i);
	std::cout << "Client " << client->getNick() << "(" << sfd  << ") "  << msg + "\n";
	if (server->getClients().find(sfd) != server->getClients().end() )
		server->getClients().erase(sfd);
}
/* ************************************************************************** */
