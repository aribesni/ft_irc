/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BufferParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchate <gduchate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:42:23 by gduchate          #+#    #+#             */
/*   Updated: 2023/03/14 15:42:27 by gduchate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFERPARSER_HPP
# define BUFFERPARSER_HPP
# include "Client.hpp"
# include <vector>
# include <string>
#include <iostream>
# include <algorithm>
# include "utils.hpp"
# include "Message.hpp"
# include "Client.hpp"
# include "Command.hpp"

class Client;

class BufferParser{
    public:
        BufferParser(std::string message);
        BufferParser(char* msg);
        BufferParser(void);
        ~BufferParser(void);
        void setMSG(char* msg);
        void setMSG(std::string msg);
        void setLines_tokens();
        void parsingCMD_init(Client &u);
        size_t      getSize();

    //private:
        std::string                                    _message;
        // std::map<std::pair<std::string, std::string>>  _singleMsg;
        std::vector<std::string>                        _lines;
        std::vector<std::vector<std::string> >          _tokens;
        std::vector<Message>                            _msgList;
        size_t                                          _msgSize;


};


#endif