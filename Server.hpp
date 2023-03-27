/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:14:04 by guillemette       #+#    #+#             */
/*   Updated: 2023/03/24 18:44:54 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# define BUFFER_SIZE 4096
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

		// METHODS
		void						fillServerPollfd(void);
		void						createSocket(void);
		void						_bind(sockaddr_in bind);
		void						_accept(Client & client);
		void						_listen(void);
		std::vector<Message>		bufferParser(char* buf, Client & client);
		void                        msg_replace(std::string &message, char find, char replace);
		void						execMultiMsg(std::vector<Message> msgList);
		void						acceptNewClient();
		void						handleClientRequest(Client & client);


		std::vector<struct pollfd>	_pollfds;
		// Client &        getClientWithFd(int fd);
		std::map<std::string, Channel>	_channels; /* channelName, Channel object*/
		void setPassword(char * password);
		
	private :
		std::string						_password;
		int								_socket;
		std::string						_name;
		char							_svc[NI_MAXSERV];
		std::map<int, Client>			_clients;

};

#endif