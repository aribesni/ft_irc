/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchate <gduchate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:43:58 by rliu              #+#    #+#             */
/*   Updated: 2023/03/24 15:19:02 by gduchate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP
#include <map>
#include <iostream>
#include <vector>
#include "Message.hpp"
#include "Channel.hpp"
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
    void    cmd_oper(std::vector<std::string>& parametre, Client& client);
    void    cmd_wallops(std::vector<std::string>& parametre, Client& client);

#endif