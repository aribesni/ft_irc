#include <poll.h>
#include <vector>
#include "Client.hpp"
#include "Server.hpp"
#include "User.hpp"

void    ft_loop(Server server)
{

    // int                         fd_count = 1;
    // char                        buf[256];
    // std::vector<class User>     user_vector;

    while (true)
    {
        // Watch pollfds and get number of open fds
        // #1: address of pollfds to watch, #2: number of pollfds to watch,
        // #3: timeout in ms. negative means infinite delay
        int open_fds = poll(&server._pollfds[0], server._pollfds.size(), -1);
        // std::cout << "#open fds: " << open_fds << std::endl;
        if (open_fds == -1) {
            perror("poll");
            exit(1);
        }
        // Run through the pollfds looking for data to read
		for (int i = 0; i < open_fds; i++)
		{
            // We're checking for the POLLIN event in all the pollfds (POLLIN='new data ready-to-read')
			if (server._pollfds[i].revents & POLLIN)
			{
                // If there is ready-to-read data in the server socket, a client tries to connect
				if (server._pollfds[i].fd == server.getSocket())
					server._acceptNewClient();
				// If there is ready-to-read data in another socket, a connected client sent data
                else
					server._handleClientRequest(i);
			}
		}
    }
}

void Server::_acceptNewClient()
{
    User    user;
    user._accept(this);

	// struct sockaddr_storage	remotaddr;
	// socklen_t				addrlen;
	// int newfd;

	// addrlen = sizeof remotaddr;
	// newfd = accept(this->_socketfd, (struct sockaddr*)&remotaddr, &addrlen);
	// if (newfd == -1)
	// 	std::cout << "accept() error: " << strerror(errno) << std::endl;
	// else
	// {
	// 	_addToPoll(newfd);
	// 	std::string welcome = _welcomemsg();
	// 	if (send(newfd, welcome.c_str(), welcome.length(), 0) == -1)
	// 		std::cout << "send() error: " << strerror(errno) << std::endl;
	// 	std::cout << "[" << currentDateTime() << "]: new connection from "
	// 		<< inet_ntoa(((struct sockaddr_in*)&remotaddr)->sin_addr)
	// 		<< " on socket " << newfd << std::endl;
	// }

    // user_vector.push_back(user);

}

void Server::_handleClientRequest(int i)
{
    (void)i;
}
    //     for (int i = 0; i < open_fds; i++)
    //     {
    //         // Check if someone's ready to read
    //         if (server._pollfds[i].revents & POLLIN)
    //         { // We got one!!
    //             // If there is data in the server socket, a client tries to connect
    //             // ssize_t recv(int sockfd, void *buf, size_t len, int flags);
    //             read(server._pollfds[i].fd, buf, sizeof(buf));
    //             std::cout << "BUF" << buf << std::endl;
    //             int nbytes = recv(server._pollfds[i].fd, buf, sizeof(buf), 0);
    //             if (server._pollfds[i].fd == server.getSocket())
    //             {
    //                 User    user;
    //                 std::cout << "nbyes" << nbytes << "in the server socket" << buf << std::endl;
    //                 user._accept(&server);
    //                 user_vector.push_back(user);
    //             }
    //             else
    //             {
    //                 // If not the listener, we're just a regular client
    //                 // int nbytes = recv(server._pollfds[i].fd, buf, sizeof(buf), 0);
    //                 int sender_fd = server._pollfds[i].fd;
    //                 if (nbytes <= 0)
    //                 {
    //                     // Got error or connection closed by client
    //                     if (nbytes == 0)
    //                         std::cout << "pollserver: socket " << sender_fd << " hung up" << std::endl;
    //                     else
    //                         perror("recv");
    //                     close(server._pollfds[i].fd); // Bye!
    //                 }
    //                 else
    //                 {
    //                     // We got some good data from a client
    //                     for (int j = 0; j < fd_count; j++) {
    //                         // Send to everyone!
    //                         // int dest_fd = client.getPfd(j).fd;
    //                         std::cout << "coucou " << buf << std::endl;
    //                         // Except the listener and ourselves
    //                         // if (dest_fd != server.getSocket() && dest_fd != sender_fd)
    //                         // {
    //                             // if (send(dest_fd, buf, nbytes, 0) == -1)
    //                             //     perror("send");
    //                         // }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
// }

int main(int argc, char **argv)
{
    // Check for correct usage
    if (argc != 2)
    {
        std::cout << "Port number needed." << std::endl;
        return (-1);
    }
    long port = std::strtol(argv[1], NULL, 10);

    // Define max number of clients
    int     max_clients = 5;

    // Create a server object with an array of pollfd (fd watchers) for each possible client connection
    Server  server(argv[0], max_clients);

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