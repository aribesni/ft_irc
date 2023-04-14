/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:12:51 by guillemette       #+#    #+#             */
/*   Updated: 2023/04/14 17:23:01 by rliu             ###   ########.fr       */
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
        std::string getIRCMode(void) const;
        std::string getHostName(void) const;
		bool		getRegistrationStatus (void);
		std::string getRealName(void) const;
		bool		getNickStatus (void) const;
		bool		getUsrStatus (void) const;
		bool		getPassStatus (void) const;
		// SETTERS
		void		setSocket(int socket);
		void		setNick(std::string &nickname);
		void		setUsr(std::string &usrname);
		void		setPass(std::string &pass);
		void		setHostname(std::string &hostname);
		void		setAsRegistered(void);
		void		setPrefix(void);
        void        setIRCMode(std::string mode);
		void		setRealname(std::string &realname);
		void		setNickRegistered(void);
		void		setUsrRegistered(void);
		void		setPassRegistered(void);

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
		std::string _irc_mode;
		std::string _realname;
		bool		_nickRegistered;
		bool		_usrRegistered;
		bool		_passRegistered;
};

// irc mode (user mode)
// i: When enabled, other users will not be able to see you on a WHO output unless they are in the channel themselves.
// w: When enabled, you will receive WALLOP messages from IRC operators.
// s: When enabled, you will receive special notices or debug messages from the server.

#endif