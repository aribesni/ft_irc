/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchate <gduchate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:43:49 by rliu              #+#    #+#             */
/*   Updated: 2023/03/22 15:49:11 by gduchate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command(void){init_command();}

Command::~Command(void){}

void Command::init_command(){
    _command["PASS"] = &cmd_pass;
    _command["NICK"] = &cmd_nick;
    _command["USER"] = &cmd_user;
    _command["PING"] = &cmd_ping;
}

void cmd_pass(std::vector<std::string> &parametre, Client &client){
    client.setPass(parametre[0]);
}
void cmd_nick(std::vector<std::string>  &parametre, Client &client){
    client.setNick(parametre[0]);
}
void cmd_user(std::vector<std::string>  &parametre, Client &client){
    client.setUsr(parametre[0]);
    client.setHostname(parametre[2]);
}
void cmd_ping(std::vector<std::string>  &parametre, Client &client){
    // As a result of server correctly responding "PONG", the irssi client interface does not
    // show [LAG] message anymore
    std::string answer = "PONG " + parametre[0] + "\r\n";
    send(client.getSocket(), answer.c_str(), answer.size(), 0);
}
