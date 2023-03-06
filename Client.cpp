#include "Client.hpp"

Client::Client(int fd_size) {

    memset(this->_host, 0, NI_MAXHOST);
    this->_pfds = std::vector<pollfd>(fd_size);
    this->_socklen = sizeof(this->_sockaddr);
}

Client::~Client(void) {}

Client::Client(const Client& src) { *this = src; }

int Client::getSocket(void) const {

    return (this->_socket);
}

pollfd Client::getPfd(int i) const {

    return (this->_pfds[i]);
}

void    Client::fillpfds(Server *server) {

    this->_pfds[0].fd = server->getSocket();
    this->_pfds[0].events = POLLIN;
}

int Client::_poll(void) {

    return (poll(&this->_pfds[0], this->_pfds.size(), -1));
}

void    add_to_pfds(std::vector<pollfd> *pfds, int newfd, int *fd_count, int *fd_size)
{
    // If we don't have room, add more space in the pfds array
    if (*fd_count == *fd_size) {
        *fd_size *= 2;
        pfds->resize(*fd_size);
    }
    (*pfds)[*fd_count].fd = newfd;
    (*pfds)[*fd_count].events = POLLIN;
    (*fd_count)++;
}

void    Client::_accept(Server *server, int *fd_count, int *fd_size) {

    this->_socket = accept(server->getSocket(), (sockaddr *)&this->_sockaddr, &this->_socklen);
    send(this->getSocket(), ":server 001 <nick> :Welcome to the <network> Network, <nick>[!<user>@<host>]\n", 78, 0);
    if (this->getSocket() == -1)
        perror("accept");
    else
    {
        add_to_pfds(&this->_pfds, this->_socket, fd_count, fd_size);
        std::cout << "pollserver: new connection from " << this->_host << " on socket " << this->_socket << std::endl;
    }
}

void    Client::del_from_pfds(int i, int *fd_count) {
    
    this->_pfds[i] = this->_pfds[*fd_count - 1];
    (*fd_count)--;
}