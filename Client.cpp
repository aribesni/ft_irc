/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchate <gduchate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:12:21 by guillemette       #+#    #+#             */
/*   Updated: 2023/04/18 14:07:03 by gduchate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Client::Client(void) : _isRegistered(false), _irc_mode(""), _nickRegistered(false), _usrRegistered(false), _passRegistered(false), _buffer("")
{
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

void	Client::addToBuffer(std::string appended)
{
	_buffer += appended;
}

void	Client::emptyBuffer(void)
{
	_buffer.clear();
}

/*
** --------------------------------- GETTERS ----------------------------------
*/

int			Client::getSocket(void) const{return (this->_socket);}

std::string	Client::getPass(void) const{return (this->_pass);}

std::string	Client::getNick(void) const{return (this->_nick);}

std::string	Client::getUser(void) const {return (this->_user);}

std::string Client::getIRCMode(void) const {return (this->_irc_mode);}

std::string Client::getHostName(void) const {return (this->_hostname);}

bool		Client::getRegistrationStatus(void) {return (this->_isRegistered);}

std::string	Client::getPrefix(void) const {return (this->_prefix);}

std::string Client::getRealName(void) const {return (this->_realname);}

bool		Client::getNickStatus (void) const{return (this->_nickRegistered);}

bool		Client::getUsrStatus (void) const{return (this->_usrRegistered);}

bool		Client::getPassStatus (void) const{return (this->_passRegistered);}

std::string	Client::getBuffer (void) const{return (this->_buffer);}

/*
** --------------------------------- SETTERS ----------------------------------
*/

void Client::setSocket(int socket)
{
	this->_socket = socket;
}

void Client::setServername(std::string servername)
{
	this->_servername = servername;
}

void  Client::setPrefix(void)
{
	_prefix = _nick + "!" + _user + "@" + _hostname;
}

void  Client::setNick(std::string &nickname)
{
	_nick = nickname;
}

void 	Client::setAsRegistered(void)
{
	_isRegistered = true;
}

void  Client::setUsr(std::string &usrname)
{
	_user = usrname;
}

void	Client::setPass(std::string &pass)
{
	_pass = pass;
}

void	Client::setHostname(std::string hostname)
{
	_hostname = hostname;
}

void	Client::setIRCMode(std::string mode)
{
	this->_irc_mode = mode;
}

void	Client::setRealname(std::string &realname)
{
	_realname = realname;
}

void	Client::setNickRegistered(void)
{
	_nickRegistered = true;
}

void	Client::setUsrRegistered(void)
{
	_usrRegistered = true;
}

void	Client::setPassRegistered(void)
{
	_passRegistered = true;
}

