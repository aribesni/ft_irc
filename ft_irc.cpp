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
        // std::cout << "#open fds: " << open_fds << std::endl;
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
					server._acceptNewConnection();
				// If there is ready-to-read data in another socket, a connected client sent data
                else
					server._handleClientRequest(server._pollfds[i].fd);
			}
		}
    }
}

// Client & Server::fd_to_client(int fd)
// {
//     // loop on all client sockets
//     std::vector<Client>::iterator it;
//     for (it = this->clients.begin(); it != this->clients.end(); ++it)
//     {
//         if ((*it).getSocket() == fd)
//             return (*it);
//     }
//     return (*it);
// }

void Server::_acceptNewConnection()
{
    Client    client;
    client._accept(this);
    struct pollfd newpollfd;
    newpollfd.fd = client.getSocket();
    newpollfd.events = POLLIN;
    this->_pollfds.push_back(newpollfd);
}

void Server::_handleClientRequest(int fd)
{

    ssize_t buff_size;
    char buf[258];

    buff_size = recv(client.getSocket(), buf, sizeof(buf), 0);
    buf[buff_size] = 0;
    std::cout << "my buf" << buf << std::endl;
    // Handle client registration by parsing [PASS]/NICK/USER commands and put set in
    send(client.getSocket(), ":server 001 <server> :Welcome to the <network> Network, <hey>[!<client>@<host>]\n", 78, 0);
    // send(client.getSocket(), welcome.c_str(), welcome.length(), 0);
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