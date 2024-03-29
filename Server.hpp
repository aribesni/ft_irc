/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:14:04 by guillemette       #+#    #+#             */
/*   Updated: 2023/04/21 10:09:14 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# define BUFFER_SIZE 4096
# ifndef DEBUG
#  define DEBUG false
# endif
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <vector>
# include <map>
# include <poll.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <string>
# include <arpa/inet.h>
# include <cstdio>
# include "Client.hpp"
# include "Message.hpp"
# include "Channel.hpp"
# include "Replies.hpp"
# include <exception>

class Message;

class Server {

	public :
		// CONSTRUCTOR / DESTRUCTOR
		Server(std::string name);
		Server(const Server& src);
		~Server(void);

		// GETTERS
		std::string					getPassword(void) const;
		int							getSocket(void) const;
		std::map<int, Client>&		getClients(void);
		std::string 				getServerName(void) const;

		// METHODS
		void						fillServerPollfd(void);
		void						createSocket(void);
		void						_bind(sockaddr_in bind);
		void						_accept(Client & client);
		void						_listen(void);
		std::vector<Message>		bufferParser(const char* buf, Client & client);
		std::vector<std::string>	msg_split(std::string str, std::string delimiter);
		void						msg_replace(std::string &message, char find, char replace);
		void						execMultiMsg(std::vector<Message> msgList);
		void						acceptNewClient();
		void						handleClientRequest(Client & client);
		int							getFdWithNick(std::string nick);
		Client						getClientWithNick(std::string nick) const;
		std::vector<struct pollfd>	_pollfds;
		// Client &        getClientWithFd(int fd);
		std::map<std::string, Channel>	_channels; /* channelName, Channel object*/
		void setPassword(char * password);
		void welcome_msg(Client &client);

		// EXCEPTIONS
		class NickNotFound : public std::exception {
			public:
				const char* what() const throw();
		};
	private :
		std::string						_password;
		int								_socket;
		std::string						_name;
		char							_svc[NI_MAXSERV];
		std::map<int, Client>			_clients;

};

#endif