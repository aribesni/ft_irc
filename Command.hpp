/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:43:58 by rliu              #+#    #+#             */
/*   Updated: 2023/04/12 19:09:40 by rliu             ###   ########.fr       */
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
#include <cstdlib>
#include <ctime>

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
	
	void	botReply(Message *message);
	

#endif