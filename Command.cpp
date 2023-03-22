/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchate <gduchate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:43:49 by rliu              #+#    #+#             */
/*   Updated: 2023/03/22 19:36:11 by gduchate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

// Command::Command(void){init_command();}

Command::Command(Client &client, Server &server, std::string commandName) : _client(client), _server(server), _name(commandName)
{
    init_command();
}

Command::~Command(void){}


void Command::init_command()
{
    _command["PASS"] = &cmd_pass;
    _command["NICK"] = &cmd_nick;
    _command["USER"] = &cmd_user;
    _command["PING"] = &cmd_ping;
    _command["JOIN"] = &cmd_join;
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
    // To be edited afterwards depending on registration checks and put in the acceptNewClient func
    client.setAsRegistered();
}

void cmd_ping(std::vector<std::string>  &parametre, Client &client){
    // As a result of server correctly responding "PONG", the irssi client interface does not
    // show [LAG] message anymore
    std::cout << "[Server] sending PONG to client (" << client.getSocket() << ")" << std::endl;
    std::string answer = "PONG " + parametre[0] + "\r\n";
    send(client.getSocket(), answer.c_str(), answer.size(), 0);
}

void cmd_join(std::vector<std::string>  &parametre, Client &client){
    // if channel name is not in the keys of the _channels map in server, then user is the first to join
    //          hence, user needs to be put as channel operator
    // add Client to the map.value vector
}

void cmd_privmsg(std::vector<std::string>  &parametre, Client &client){
    // if second arg starts with # then it is intended for a channel
    //      get the list of clients in the channel and send message to all except the client itself
}