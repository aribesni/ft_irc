/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:27:53 by rliu              #+#    #+#             */
/*   Updated: 2023/03/10 07:31:27 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include "utils.hpp"


//save recv message
Message::Message(void):_msgSize(0){}

Message::Message(std::string message):_message(message),_msgSize(0){
   setLines_tokens();   
}
Message::Message(char* message):_msgSize(0){
    _message = message;
   setLines_tokens();   
}

Message::~Message(void){}


void Message::setMSG(std::string msg){
    _message = msg;
    setLines_tokens();
}

void Message::setMSG(char* msg){
    _message = msg;
    setLines_tokens();
}

void Message::setLines_tokens(){
     _lines= msg_split(_message, "\r\n");
     _msgSize = _lines.size();
    for (size_t i=0; i<getSize(); ++i){
        //
        _tokens.push_back(msg_split(_lines[i], " "));
    }
}

std::string Message::getNick(){return (this->_nick);};
std::string Message::getUser(){return (this->_user);};
std::string Message::getPrefix(){return (this->_prefix);};
std::string Message::getPass(){return (this->_pass);};
size_t      Message::getSize(){return (this->_msgSize);};
    
void Message::parsingCMD_init(){
    std::string nickname;
    for (size_t i=0; i<getSize(); ++i){
        if(_tokens[i][0] == "PASS") {
            _pass = _tokens[i][1]; 
        }
        else if(_tokens[i][0] == "USER"){
            _user = _tokens[i][1];
            _host = _tokens[i][3];
        } 
        else if(_tokens[i][0] == "NICK") 
            _nick = _tokens[i][1];
    }
    _prefix = _nick + "!" + _user + "@" + _host;  
    _cmd._command["PASS"](_tokens[1]); // this is a test for Command class;
}
    
        