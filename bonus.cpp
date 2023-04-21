/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:30:12 by rliu              #+#    #+#             */
/*   Updated: 2023/04/21 10:22:59 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
----to transfer file 
1. /set dcc_upload_path .
2./set dcc_download_path ~/Downloads
3. /set dcc_autoget on
4. /DCC send <nick> <filename> "<< PRIVMSG _rliu_ :DCC SEND test2023_now 168495108 41815 14"
5. ">>:_rliu!~rliu@6cd7-bcd-b63-9ddf-8c58.210.62.ip PRIVMSG _rliu_ :DCC SEND test2023_now 168495108 41815 14"
-----bot
1. /join bot
question:
*/

#include "Command.hpp"
#include <string>
#include <cstdlib>
#include <ctime>

std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

void botReply(Message *message){
    
    std::string msg = message->getFullMsg();
    std::string msgLower;
    std::string msgSend = ":#bot PRIVMSG #bot :";
    int pos = msg.find(":");
    msg = msg.substr(pos);
    for (size_t i = 1; i < msg.size(); i++)
            msgLower += tolower(msg[i]);
    if (msgLower == "help")
        msgSend += "You can ask bot: help; Hello; Bonjour; What's the time now?; Where are you?; Tell me a joke; Nickname; Realname; Servername;";
    else if (msgLower == "bonjour")
        msgSend += "Bonjour";
    else if (msgLower == "hello")
        msgSend += "Hello, how are you?";
    else if (msgLower == "what's the time now?")
        msgSend += "The time now: " + currentDateTime();
    else if (msgLower == "where are you?"){
        msgSend += "I am in 42 School with you";   
    }
    else if (msgLower == "tell me a joke")
        msgSend += " – Maman, maman, j’ai vu un zinc!  – D’accord, mais non mon chéri, il vaut mieux dire avion. – Ah, d’accord : J’avions vu un zinc.";
     else if (msgLower == "nickname")
        msgSend += message->getClient()->getNick();
    else if (msgLower == "realname")
        msgSend += message->getClient()->getRealName();
    else if (msgLower == "servername")
    {
        std::string servername = message->getServer()->getServerName();
        msgSend += servername.substr(2, servername.size()-2);
    }
    else
        msgSend += "It's a good question, let me think about, have a good day! You could also type \"help\"."; 
    msgSend += "\r\n";
    send(message->getClient()->getSocket(), msgSend.c_str(), msgSend.size(), 0);    
}


