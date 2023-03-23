/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:43:49 by rliu              #+#    #+#             */
/*   Updated: 2023/03/23 18:39:13 by rliu             ###   ########.fr       */
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

void rplSender(Client &client, std::string code){
    Replies replies;
    replies.getReplies(client.getNick(), client.getUser(), client.getPrefix());
    std::string reply = replies._replies[code];
    send(client.getSocket(), reply.c_str(), reply.size(), 0);
}

void msgSender(Client &client, std::string cmd, std::string msg){
    std::string msgSend = client.getPrefix() + " " + cmd + " " + msg + "/r/n";
    send(client.getSocket(), msgSend.c_str(), msgSend.size(), 0);
}

void cmd_pass(std::vector<std::string> &parametre, Client &client){
    if (client.getPassword() != parametre[0]){
        std::cout << "wrong password\n"; 
        return;
    }
    else
        client.setPass(parametre[0]);
}

void cmd_nick(std::vector<std::string>  &parametre, Client &client){
    int code = client.setNick(parametre[0]);
    if(code){
        std::ostringstream oOStrStream;
        oOStrStream << code;
        rplSender(client, oOStrStream.str());// how to send reason ?
    }
    if (client.getNick() != parametre[0])
        msgSender(client, "NICK", client.getNick());
}

void cmd_user(std::vector<std::string>  &parametre, Client &client){
    client.setUsr(parametre[0]);
    client.setHostname(parametre[2]);
    // To be edited afterwards depending on registration checks and put in the acceptNewClient func
}

void cmd_ping(std::vector<std::string>  &parametre, Client &client){
    // As a result of server correctly responding "PONG", the irssi client interface does not
    // show [LAG] message anymore
    std::cout << "[Server] sending PONG to client (" << client.getSocket() << ")" << std::endl;
    std::string answer = "PONG " + parametre[0] + "\r\n";
    send(client.getSocket(), answer.c_str(), answer.size(), 0);
}
