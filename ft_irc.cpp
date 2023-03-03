#include <poll.h>
#include <vector>
#include "Client.hpp"
#include "Server.hpp"

// Get sockaddr, IPv4 or IPv6:
void *get_in_addr(sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return &(((sockaddr_in*)sa)->sin_addr);
    return &(((sockaddr_in6*)sa)->sin6_addr);
}

// Return a listening socket
int get_listener_socket(char *port)
{
    int listener;     // Listening socket descriptor
    int yes = 1;      // For setsockopt() SO_REUSEADDR, below
    int rv;

    addrinfo hints, *ai, *p;

    // Get us a socket and bind it
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, port, &hints, &ai)) != 0) {
        std::cerr << "selectserver: " << gai_strerror(rv) << std::endl;
        exit(1);
    }

    for(p = ai; p != NULL; p = p->ai_next) {
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0)
            continue;

        // Lose the pesky "address already in use" error message
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }
        break;
    }

    // If we got here, it means we didn't get bound
    if (p == NULL)
        return (-1);

    freeaddrinfo(ai); // All done with this

    // Listen
    if (listen(listener, 10) == -1)
        return (-1);
    return (listener);
}

// Add a new file descriptor to the set
void add_to_pfds(std::vector<pollfd> *pfds, int newfd, int *fd_count, int *fd_size)
{
    // If we don't have room, add more space in the pfds array
    if (*fd_count == *fd_size) {
        *fd_size *= 2; // Double it

        pfds->resize(*fd_size);
        // *pfds = (pollfd*)realloc(*pfds, sizeof(**pfds) * (*fd_size));
    }

    (*pfds)[*fd_count].fd = newfd;
    (*pfds)[*fd_count].events = POLLIN; // Check ready-to-read

    (*fd_count)++;
}

// Remove an index from the set
void del_from_pfds(std::vector<pollfd> pfds, int i, int *fd_count)
{
    // Copy the one from the end over this one
    pfds[i] = pfds[*fd_count - 1];
    (*fd_count)--;
}

// Main
int main(int argc, char **argv)
{

    if (argc != 2)
    {
        std::cout << "Port number needed." << std::endl;
        return (-1);
    }

    Client  client;
    Server  server;

    //server socket

    server._name = argv[0];
    client._port = std::strtol(argv[1], NULL, 10);

    char             buf[256];    // Buffer for client data

    // Start off with room for 5 connections
    // (We'll realloc as necessary)
    int               fd_count = 0;
    int               fd_size = 5;
    // pollfd            *pfds = (pollfd*)malloc(sizeof(*pfds) * fd_size);

    std::vector<pollfd> pfds(fd_size);

    // Set up and get a listening socket
    server._socket = get_listener_socket(argv[1]);

    if (server._socket == -1) {
        std::cerr << "error getting listening socket" << std::endl;
        exit(1);
    }

    // Add the listener to set
    pfds[0].fd = server._socket;
    pfds[0].events = POLLIN; // Report ready to read on incoming connection

    fd_count = 1; // For the listener

    // Main loop
    while (true)
    {
        int poll_count = poll(&pfds[0], pfds.size(), -1);

        if (poll_count == -1) {
            perror("poll");
            exit(1);
        }

        // Run through the existing connections looking for data to read
        for(int i = 0; i < fd_count; i++) {

            // Check if someone's ready to read
            if (pfds[i].revents & POLLIN) { // We got one!!

                if (pfds[i].fd == server._socket) {
                    // If listener is ready to read, handle new connection

                    client._socklen = sizeof(client._sockaddr);
                    client._socket = accept(server._socket, (sockaddr *)&client._sockaddr, &client._socklen);
                    
                    send(client._socket, ":server 001 <nick> :Welcome to the <network> Network, <nick>[!<user>@<host>]\n", 78, 0);

                    if (client._socket == -1)
                        perror("accept");
                    else
                    {
                        add_to_pfds(&pfds, client._socket, &fd_count, &fd_size);
                        std::cout << "pollserver: new connection from " << inet_ntoa(client._sockaddr.sin_addr) << " on socket " << client._socket << std::endl;
                    }
                }
                else
                {
                    // If not the listener, we're just a regular client
                    int nbytes = recv(pfds[i].fd, buf, sizeof(buf), 0);

                    int sender_fd = pfds[i].fd;

                    if (nbytes <= 0)
                    {
                        // Got error or connection closed by client
                        if (nbytes == 0)
                            std::cout << "pollserver: socket " << sender_fd << " hung up" << std::endl;
                        else
                            perror("recv");

                        close(pfds[i].fd); // Bye!

                        del_from_pfds(pfds, i, &fd_count);
                    }
                    else
                    {
                        // We got some good data from a client
                        for(int j = 0; j < fd_count; j++) {
                            // Send to everyone!
                            int dest_fd = pfds[j].fd;

                            // Except the listener and ourselves
                            if (dest_fd != server._socket && dest_fd != sender_fd)
                            {
                                if (send(dest_fd, buf, nbytes, 0) == -1)
                                    perror("send");
                            }
                        }
                    }
                }
            }
        }
    }
    return (0);
}