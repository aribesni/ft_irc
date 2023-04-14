/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillemette.duchateau <guillemette.duch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:43:58 by rliu              #+#    #+#             */
/*   Updated: 2023/04/13 12:44:37 by guillemette      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include "Message.hpp"
#include "Channel.hpp"
#include <string>

#define USERMODEFLAGS "iswo"
#define CHANMODEFLAGS "oitnk"

struct modes {
	std::string	raw;
	char		sign;
	std::string	match;
	std::string	ret;
};

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
	void	cmd_pass(Message* message);
	void	cmd_nick(Message* message);
	void	cmd_user(Message* message);
	void	cmd_ping(Message* message);
	void	cmd_join(Message* message);
	void	cmd_privmsg(Message* message);
	void	cmd_part(Message* message);
	void	cmd_oper(Message* message);
	void	cmd_wallops(Message* message);
	void	cmd_kill(Message * message);
	void	cmd_kick(Message * message);
	void	cmd_notice(Message * message);
	void	cmd_whois(Message * message);
	void	cmd_invite(Message * message);
	void	cmd_mode(Message * message);

#endif