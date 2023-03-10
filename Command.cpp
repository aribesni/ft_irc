/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:43:49 by rliu              #+#    #+#             */
/*   Updated: 2023/03/10 07:34:22 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
Command::Command(void){init_command();}

Command::~Command(void){}



void Command::init_command(){
     _command["PASS"] = &check_pass;
}

void check_pass(std::vector<std::string> cmd){
    
    std::cout << "Command test: Command: " << cmd[0] << " Parametres:"<< cmd[1] << std::endl;
}