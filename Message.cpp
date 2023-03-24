/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchate <gduchate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:13:55 by guillemette       #+#    #+#             */
/*   Updated: 2023/03/24 16:10:30 by gduchate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include "Command.hpp"

Command     g_cmd;

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

// Message::Message(void){}

Message::Message(std::vector<std::string> &tokens, Client *client, Server *server, std::string fullMsg) :
	_fullMsg(fullMsg), _cmd(tokens[0]), _params(tokens.begin()+1, tokens.end()), _client(client), _server(server)
{
	// Display tokens
	// for (size_t i = 0; i < tokens.size(); i++)
	//     std::cout << "token " << i << ": " << tokens[i] << std::endl;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Message::~Message(void){}

/*
** --------------------------------- METHODS ----------------------------------
*/

void						Message::execCmd()
{
	if(g_cmd._cmdMap.find(_cmd) != g_cmd._cmdMap.end())
	{
		std::cout << "[Client] (" << _client->getSocket() << ") Command " << _cmd << " is being processed." << std::endl;
		g_cmd._cmdMap[_cmd](this);
	}
	else
		std::cout << "[Client] (" << _client->getSocket() << ") Command " << _cmd << " not found." << std::endl;
}

/*
** --------------------------------- GETTERS ----------------------------------
*/

std::string 				Message::getFullMsg(void) const {return(_fullMsg);}

std::string 				Message::getCMD(void) const {return(_cmd);}

std::vector<std::string>	Message::getParams(void) const {return(_params);}

Server* 				    Message::getServer(void) const {return(_server);}

Client* 				    Message::getClient(void) const {return(_client);}

/* ************************************************************************** */