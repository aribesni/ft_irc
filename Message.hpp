/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillemette.duchateau <guillemette.duch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:13:57 by guillemette       #+#    #+#             */
/*   Updated: 2023/03/23 18:25:12 by guillemette      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>
# include <vector>
# include <map>
# include "Server.hpp"
# include "Client.hpp"


class Server;
class Client;
class Message
{
	public:
		// CONSTRUCTOR / DESTRUCTOR
		// Message(void);
		Message(std::vector<std::string> &tokens, Client &client, Server *server);
		~Message(void);

		// GETTERS
		std::string 				getCMD(void) const;
		std::vector<std::string>	getParams(void) const;
		Server*						getServer(void) const;
		Client&						getClient(void) const;

		// METHODS
		void						execCmd();

	private:
		std::string																_prefix;
		std::string																_cmd;
		std::vector<std::string>												_params;
		Client&																	_client;
		Server*																	_server;
};

#endif