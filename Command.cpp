/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:43:49 by rliu              #+#    #+#             */
/*   Updated: 2023/03/16 16:40:36 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command(void){init_command();}

Command::~Command(void){}

void Command::init_command(){
    _command["PASS"] = &cmd_pass;
    _command["NICK"] = &cmd_nick;
    _command["USER"] = &cmd_user;
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
