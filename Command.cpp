/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:43:49 by rliu              #+#    #+#             */
/*   Updated: 2023/03/16 11:39:28 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command(void){init_command();}

Command::~Command(void){}

void    Command::init_command(){
    _command["PASS"] = &cmd_pass;
    _command["NICK"] = &cmd_nick;
    _command["USER"] = &cmd_user;
    _command["OPER"] = &cmd_oper;
}

void    cmd_pass(std::vector<std::string> &parametre, Client *client) {
    client->setPass(parametre[0]);
}
void    cmd_nick(std::vector<std::string> &parametre, Client *client) {
    client->setNick(parametre[0]);
}
void    cmd_user(std::vector<std::string> &parametre, Client *client) {
    client->setUsr(parametre[0]);
    client->setHostname(parametre[2]);
}
void    cmd_oper(std::vector<std::string> &parametre, Client *client) {

    (void)client;
    Replies replies(client);

    if (/*parametre[0] == "operator" &&*/ parametre[1] == "password")
        send(client->getSocket(), replies.RPL_YOUREOPER("381").data(), replies.RPL_YOUREOPER("381").size(), 0);
}
