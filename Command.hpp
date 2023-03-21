/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:43:58 by rliu              #+#    #+#             */
/*   Updated: 2023/03/16 16:39:35 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP
#include <map>
#include <iostream>
#include <vector>
#include "Client.hpp"
#include "Server.hpp"
#include "Message.hpp"

class Client;

class Command{
    public:
        Command(void);
        ~Command(void);

        void init_command();

        std::map<std::string, void(*)(std::vector<std::string>&, Client&)>	_command;
};

//fuctions of cmd
void cmd_pass(std::vector<std::string>&  parametre, Client& client);
void cmd_nick(std::vector<std::string>&  parametre, Client& client);
void cmd_user(std::vector<std::string>&  parametre, Client& client);


#endif