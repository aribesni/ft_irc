/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BufferParser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchate <gduchate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:27:53 by rliu              #+#    #+#             */
/*   Updated: 2023/03/14 14:50:38 by gduchate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BufferParser.hpp"
#include "utils.hpp"

//save recv message
BufferParser(void):_msgSize(0){}

BufferParser::BufferParser(std::string message):_message(message),_msgSize(0){
   setLines_tokens();
}
BufferParser::BufferParser(char* message):_msgSize(0){
    _message = message;
   setLines_tokens();
}

BufferParser::~BufferParser(void){}


void BufferParser::setMSG(std::string msg){
    _message = msg;
    setLines_tokens();
}

void BufferParser::setMSG(char* msg){
    _message = msg;
    setLines_tokens();
}

void BufferParser::setLines_tokens(){
     _lines= msg_split(_message, "\r\n");
     _msgSize = _lines.size();
    _msgList.resize(_msgSize);
    for (size_t i=0; i<getSize(); ++i){

        _tokens.push_back(msg_split(_lines[i], " "));
        _msgList[i].cmd = _tokens[i][0];
        _msgList[i].paramList.insert(_msgList[i].paramList.begin(),_tokens[i].begin()+1,_tokens[i].end());
}
}

size_t      BufferParser::getSize(){return (this->_msgSize);};

void BufferParser::parsingCMD_init(Client& u){

    Command cmd;
    for (size_t i=0; i < getSize(); ++i){
        if(cmd._command.find(_msgList[i].cmd) != cmd._command.end())
            cmd._command[_msgList[i].cmd](_msgList[i].paramList, u);
    }
}

// void cmd_nick(std::vector<string>  parametre, Client &u){

// }