/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillemette.duchateau <guillemette.duch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:43:58 by rliu              #+#    #+#             */
/*   Updated: 2023/03/23 18:27:30 by guillemette      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP
#include <map>
#include <iostream>
#include <vector>
#include "Message.hpp"

class Client;

class Command
{
	private:
	public:
		Command(void);
		~Command(void);

		void initCmdMap();
		std::map<std::string, void(*)(Message*)>	_cmdMap;
};

// CMD
	void cmd_pass(Message* message);
	void cmd_nick(Message* message);
	void cmd_user(Message* message);
	void cmd_ping(Message* message);
	void cmd_join(Message* message);

#endif