/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchate <gduchate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:13:49 by guillemette       #+#    #+#             */
/*   Updated: 2023/04/04 14:47:41 by gduchate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <poll.h>
#include <vector>
#include <signal.h>
#include "Server.hpp"
#include "Client.hpp"
#include "Replies.hpp"

bool sig = false;

void	sigHandler(int signum) {

	(void)signum;
	// std::cout << std::endl << "SIGNAL " << signum << " CAUGHT" << std::endl;
	sig = true;
}

void    ft_loop(Server server)
{
	// signal(SIGINT, sigHandler);
	// while (sig == false)
	while (true)
	{
		// Watch pollfds and get number of open fds
		// #1: address of pollfds to watch, #2: number of pollfds to watch,
		// #3: timeout in ms. negative means infinite delay
		int open_fds = poll(&server._pollfds[0], server._pollfds.size(), -1);
		// poll(&server._pollfds[0], server._pollfds.size(), -1);
		// Handle poll error
		if (open_fds == -1)
		{
			perror("poll");
			exit(1);
		}
		// Run through the pollfds looking for data to read
		for (size_t i = 0; i < server._pollfds.size(); i++)
		{
			// std::cout << "number of open fds" << server.getClients().size() + 1 << std::endl;
			// We're checking for the POLLIN event in all the pollfds (POLLIN='new data ready-to-read')
			if (server._pollfds[i].revents & POLLIN)
			{
				// If there is ready-to-read data in the server socket, a client tries to connect
				if (server._pollfds[i].fd == server.getSocket())
					server.acceptNewClient();
				// If there is ready-to-read data in another socket, a connected client sent data
				else
					server.handleClientRequest(server.getClients()[server._pollfds[i].fd]);
			}
		}
	}
}

int main(int argc, char **argv)
{
	// Check for correct usage
    if (argc != 3)
    {
        std::cout << "Port number and password needed." << std::endl;
        return (-1);
    }

	long port = std::strtol(argv[1], NULL, 10);

	// Create a server object
	Server  server(argv[0]);
	server.setPassword(argv[2]);
	// Create server socket
	server.createSocket();

	// Specify server socket address characteristics
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.s_addr = INADDR_ANY; /* listens to all the local interfaces (all local IP addresses)*/

	// Bind server socket to an address specified by hint
	server._bind(hint);

	// Make the server socket listen
	server._listen();

	// Fill server pollfd (_pollfds[0]) with server socket infos
	server.fillServerPollfd();

	// Start infinite loop
	ft_loop(server);

	return (0);
}