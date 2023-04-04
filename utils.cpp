/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchate <gduchate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:53:01 by gduchate          #+#    #+#             */
/*   Updated: 2023/04/04 17:53:10 by gduchate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::vector<std::string>*		msgtargetToVecttarget(std::string msgtarget)
{
	std::vector<std::string>* vecttarget = new std::vector<std::string>();
	// Check if msgtarget does not start or end with ,

	size_t i = 0;

	while( i < msgtarget.length())
	{
		if (msgtarget[i] == ',')
		{
			vecttarget->push_back(msgtarget.substr(0, i - 1));
			msgtarget = msgtarget.substr(i + 1);
			i = 0;
		}
		i++;
	}
	vecttarget->push_back(msgtarget);
	std::cout << "Print targets: ";
	for (size_t j = 0; j < vecttarget->size(); j++)
		std::cout << (*vecttarget)[j] << " ";

	return (vecttarget);
}