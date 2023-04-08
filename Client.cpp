/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillemette.duchateau <guillemette.duch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:12:21 by guillemette       #+#    #+#             */
/*   Updated: 2023/04/08 11:09:09 by guillemette      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Client::Client(void) : _isRegistered(false) {
// TO DO: Change memset to a c++ method/func
	memset(this->_host, 0, NI_MAXHOST);
	this->_socklen = sizeof(this->_sockaddr);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Client::~Client(void) {}


/*
** --------------------------------- METHODS ----------------------------------
*/


/*
** --------------------------------- GETTERS ----------------------------------
*/

int			Client::getSocket(void) const{return (this->_socket);}

std::string	Client::getPass(void) const{return (this->_pass);}

std::string	Client::getNick(void) const{return (this->_nick);}

std::string	Client::getUser(void) const {return (this->_user);}

std::string Client::getIRCMode(void) const {return (this->_irc_mode);}

std::string Client::getHostName(void) const {return (this->_hostname);}

bool		Client::getRegistrationStatus(void) const {return (this->_isRegistered);}

std::string	Client::getPrefix(void) const {return (this->_prefix);}

/*
** --------------------------------- SETTERS ----------------------------------
*/

void Client::setSocket(int socket)
{
	this->_socket = socket;
}

void  Client::setPrefix(void)
{
		_prefix = _nick + "!" + _user + "@" + _hostname;
//      _msgWelcome = ":" + _prefix + " 001 " + _nick + " :Welcome to the IRC__ Network, " + _prefix + "\n";
	   // std::cout << "test_setprefic: "<<_prefix << std::endl;
 }

void  Client::setNick(std::string &nickname)
{
	_nick = nickname;
}

void  Client::setAsRegistered(void){
    _isRegistered = true;
    this->setIRCMode("wi");
}

void  Client::setUsr(std::string &usrname)
{
	_user = usrname;
}

void  Client::setPass(std::string &pass)
{
	_pass = pass;
}

void  Client::setHostname(std::string &hostname)
{
	_hostname = hostname;
}

void    Client::setIRCMode(std::string mode) {

    this->_irc_mode = mode;
}
