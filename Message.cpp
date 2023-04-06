/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillemette.duchateau <guillemette.duch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:13:55 by guillemette       #+#    #+#             */
/*   Updated: 2023/04/06 19:09:34 by guillemette      ###   ########.fr       */
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
	if (!_params.empty())
		this->setTargets(_params[0]);
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
		// std::cout << "[Client] (" << _client->getSocket() << ") Command " << _cmd << " is being processed." << std::endl;
		g_cmd._cmdMap[_cmd](this);
	}
	// else
		// std::cout << "[Client] (" << _client->getSocket() << ") Command " << _cmd << " not found." << std::endl;
}

void		Message::setTargets(std::string msgtarget)
{
	// Check if msgtarget does not start or end with ,

	size_t i = 0;

	while( i < msgtarget.length())
	{
		if (msgtarget[i] == ',')
		{
			_targets.push_back(msgtarget.substr(0, i - 1));
			msgtarget = msgtarget.substr(i + 1);
			i = 0;
		}
		i++;
	}
	_targets.push_back(msgtarget);
	// if (DEBUG && !_targets.empty())
	// {
	// 	std::cout << "Print targets: ";
	// 	for (size_t j = 0; j < _targets.size(); j++)
	// 		std::cout << _targets[j] << " ";
	// }
}

/*
** --------------------------------- GETTERS ----------------------------------
*/

std::string 				Message::getFullMsg(void) const {return(_fullMsg);}

std::string 				Message::getCMD(void) const {return(_cmd);}

std::vector<std::string>	Message::getParams(void) const {return(_params);}

Server* 				    Message::getServer(void) const {return(_server);}

Client* 				    Message::getClient(void) const {return(_client);}

std::vector<std::string> 	Message::getTargets(void) const {return(_targets);}

/* ************************************************************************** */