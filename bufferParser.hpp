/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:42:23 by gduchate          #+#    #+#             */
/*   Updated: 2023/03/16 11:56:08 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFERPARSER_HPP
# define BUFFERPARSER_HPP
# include "Client.hpp"
# include <vector>
# include <string>
#include <iostream>
# include <algorithm>
# include "Message.hpp"
# include "Client.hpp"
# include "Command.hpp"

std::vector<Message>  bufferParser(char* buf);
void multiMessge_exec(std::vector<Message> msgList, Client &client);

#endif