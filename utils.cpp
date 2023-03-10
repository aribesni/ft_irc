/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:08:28 by rliu              #+#    #+#             */
/*   Updated: 2023/03/09 16:07:13 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::vector<std::string> msg_split(std::string str, std::string delimiter)
{
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


