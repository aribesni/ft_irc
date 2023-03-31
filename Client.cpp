/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:12:21 by guillemette       #+#    #+#             */
/*   Updated: 2023/03/24 19:55:21 by rliu             ###   ########.fr       */
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

std::string Client::getChanMode(void) const {return (this->_chan_mode);}

std::string Client::getHostName(void) const {return (this->_hostname);}

bool Client::getRegistrationStatus(void) const {return (this->_isRegistered);}

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
	//std::cout << "test_nick: " << _nick << std::endl;
}

void  Client::setAsRegistered(void){
    _isRegistered = true;
    this->setIRCMode("wi");
}

void  Client::setUsr(std::string &usrname)
{
	_user = usrname;
	//std::cout << "test_user: " << _user<< std::endl;
}

void  Client::setPass(std::string &pass)
{
	_pass = pass;
	//std::cout << "test_pass: " << _pass << std::endl;
}

void  Client::setHostname(std::string &hostname){
    _hostname = hostname;
    //std::cout << "test_pass: " << _hostname << std::endl;
}

void    Client::setIRCMode(std::string mode) {

    this->_irc_mode = mode;
}

void    Client::setChanMode(std::string mode) {

    this->_chan_mode = mode;
}
