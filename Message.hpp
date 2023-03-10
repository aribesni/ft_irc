/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:18:42 by rliu              #+#    #+#             */
/*   Updated: 2023/03/09 18:22:09 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MESSAGE_HPP
# define MESSAGE_HPP
# include "Client.hpp"
# include <vector>
# include <string>
#include <iostream>
# include <algorithm>
# include "utils.hpp"
# include "User.hpp"
# include "Command.hpp"
class User;
class Command;
class Message{
    public:
        Message(std::string message);
        Message(char* msg);
        Message(void);
        ~Message(void);
        void setMSG(char* msg);
        void setMSG(std::string msg);
        void setLines_tokens();
        std::string getNick();
        std::string command_Nick();//is it necessary une class command?
        void print_tokens();
        void parsingCMD_init();
        std::string getUser();
        std::string getPrefix();
        std::string getPass();
        size_t      getSize();
        
    //private:    
        std::string                                    _message;
        // std::map<std::pair<std::string, std::string>>  _singleMsg;
        std::vector<std::string>                        _lines;
        std::vector<std::vector<std::string> >          _tokens;
        std::string                                     _nick; //tmp it will save in user
        std::string                                     _pass; //tmp
        std::string                                     _user; //tmp
        std::string                                     _host;
        std::string                                     _prefix;//tmp
        size_t                                          _msgSize;
        Command                                         _cmd;
        
};


#endif