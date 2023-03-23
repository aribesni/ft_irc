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

#include "bufferParser.hpp"

// split by delimiter
std::vector<std::string> msg_split(std::string str, std::string delimiter)
{
	// std::vector<std::string> tokens = std::vector<std::string>();

	// size_t end;
	// while ((end = str.find(delimiter)) != std::string::npos || str == "\n")
	// {
	// 	tokens.push_back(str.substr(0, end));
	// 	str = str.substr(end + delimiter.size());
	// }
    // if (str != "")
	//     tokens.push_back(str);
	// return tokens;

	std::vector<std::string> tokens = std::vector<std::string>();

	int end;
	while ((end = str.find(delimiter)) != -1)
	{
		tokens.push_back(str.substr(0, end));
		str.erase(0, end + delimiter.length());
	}
	tokens.push_back(str);
	return tokens;
}


// Parser buffer from char * to a vector of class Message
std::vector<Message>  bufferParser(char* buf){
    std::string                                     message(buf);
    std::vector<std::string>                        lines;
    std::vector<std::vector<std::string> >          tokens;
    std::vector<Message>                            msgList;
    size_t                                          msgSize = 0;

    // message = buf;
    lines = msg_split(message, "\r\n");
    // Display lines vector
    msgSize = lines.size();
    for (size_t i = 0; i < msgSize; i++)
    {
        tokens.push_back(msg_split(lines[i], " "));
        Message msg(tokens[i]);
        msgList.push_back(msg);
    }
    return (msgList);
}

// excute every message
void multiMessge_exec(std::vector<Message> msgList, Client& client){
    for (size_t i=0; i < msgList.size(); ++i)
        msgList[i].execCMD(client);
}