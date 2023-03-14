#include <poll.h>
#include <vector>
#include "Server.hpp"
#include "Client.hpp"

void    ft_loop(Server server)
{
    while (true)
    {
        // Watch pollfds and get number of open fds
        // #1: address of pollfds to watch, #2: number of pollfds to watch,
        // #3: timeout in ms. negative means infinite delay
        int open_fds = poll(&server._pollfds[0], server._pollfds.size(), -1);
        // Handle poll error
        if (open_fds == -1)
        {
            perror("poll");
            exit(1);
        }
        // Run through the pollfds looking for data to read
		for (int i = 0; i < open_fds + 1; i++)
		{
            // We're checking for the POLLIN event in all the pollfds (POLLIN='new data ready-to-read')
			if (server._pollfds[i].revents & POLLIN)
			{
                // If there is ready-to-read data in the server socket, a client tries to connect
				if (server._pollfds[i].fd == server.getSocket())
					server.acceptNewConnection();
				// If there is ready-to-read data in another socket, a connected client sent data
                else
                    server.handleClientRequest(server.clients[server._pollfds[i].fd]);
			}
		}
    }
}

void Server::acceptNewConnection()
{
    Client    client;
    this->_accept(client);
    struct pollfd newpollfd;
    newpollfd.fd = client.getSocket();
    newpollfd.events = POLLIN;
    this->_pollfds.push_back(newpollfd);
    this->clients[newpollfd.fd] = client;
}

void Server::handleClientRequest(Client & client)
{
    // Handle client registration
    if (client.getRegistrationStatus() == false)
    {
        // 1- Parse registration messages and get client nick, user and password
        // 2- Check user and nick format
        // 3- Check password
        // 4- If correct registration, server sends block of welcome message
        // send(this->getSocket(), this->_replies.RPL_WELCOME("001").data(), this->_replies.RPL_WELCOME("001").size(), 0);
        // send(this->getSocket(), this->_replies.RPL_YOURHOST("002").data(), this->_replies.RPL_YOURHOST("002").size(), 0);
        // send(this->getSocket(), this->_replies.RPL_CREATED("003").data(), this->_replies.RPL_CREATED("003").size(), 0);
        // send(this->getSocket(), this->_replies.RPL_MYINFO("004").data(), this->_replies.RPL_MYINFO("004").size() - 1, 0);
        // send(this->getSocket(), this->_replies.RPL_MOTD("372").data(), this->_replies.RPL_MOTD("372").size(), 0);
        // send(this->getSocket(), this->_replies.RPL_MOTDSTART("375").data(), this->_replies.RPL_MOTDSTART("375").size(), 0);
        // send(this->getSocket(), this->_replies.RPL_ENDOFMOTD("376").data(), this->_replies.RPL_ENDOFMOTD("376").size(), 0);
    }
    else if (client.getRegistrationStatus() == true)
    {
        // Handle other requests
        // WIP
        ssize_t buff_size;
        char buf[BUFFER_SIZE];
        // Loop on buff till we get a end of message delimiter /r/n
        buff_size = recv(client.getSocket(), buf, sizeof(buf), 0);
        std::cout << "buff size" << buff_size << std::endl;
        buf[buff_size] = 0;
        std::cout << "my buf" << buf << std::endl;
        // PRIVATE MESSAGE
        //     for (int j = 0; j < fd_count; j++)
        // {
        // 	// Send to everyone!
        // 	int dest_fd = server.getPfd(j).fd;

        // 	// Except the listener and ourselves
        // 	if (dest_fd != server.getSocket() && dest_fd != sender_fd)
        // 	{
        // 		if (send(dest_fd, buf, nbytes, 0) == -1)
        // 			perror("send");
        // 	}
        // }
    }
}

int main(int argc, char **argv)
{
    // Check for correct usage
    if (argc != 2)
    {
        std::cout << "Port number needed." << std::endl;
        return (-1);
    }
    long port = std::strtol(argv[1], NULL, 10);

    // Create a server object
    Server  server(argv[0]);

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