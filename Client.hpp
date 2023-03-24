/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:12:51 by guillemette       #+#    #+#             */
/*   Updated: 2023/03/24 19:52:35 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <iostream>
# include <netdb.h>
# include <string.h>

class Client {

	public :
		// CONSTRUCTOR / DESTRUCTOR
		Client(void);
		~Client(void);

		// GETTERS
		int			getSocket(void) const;
		std::string getPass(void) const;
		std::string	getNick(void) const;
		std::string	getUser(void) const;
		std::string	getPrefix(void) const;
		bool		getRegistrationStatus (void) const;

		// SETTERS
		void		setSocket(int socket);
		void		setNick(std::string &nickname);
		void		setUsr(std::string &usrname);
		void		setPass(std::string &pass);
		void		setHostname(std::string &hostname);
		void		setAsRegistered(void);
		void		setPrefix(void);

		sockaddr_in _sockaddr;
		socklen_t   _socklen;

	private :
		std::string	_password;
		int			_socket;
		char		_host[NI_MAXHOST];
		bool		_isRegistered;
		std::string	_prefix;
		std::string	_hostname;
		std::string	_user;
		std::string	_nick;
		std::string	_pass;
		std::string	_msgWelcome;
};

#endif