#include "User.hpp"

User::User(void) {

    memset(this->_host, 0, NI_MAXHOST);
    this->_socklen = sizeof(this->_sockaddr);
}

User::~User(void) {}

int User::getSocket(void) const {

    return (this->_socket);
}

void    User::_accept(Client *client, Server *server, int *fd_count, int *fd_size) {

    this->_socket = accept(server->getSocket(), (sockaddr *)&this->_sockaddr, &this->_socklen);
    send(this->getSocket(), ":server 001 <nick> :Welcome to the <network> Network, <nick>[!<user>@<host>]\n", 78, 0);
    if (this->getSocket() == -1)
        perror("accept");
    else
    {
        client->add_to_pfds(this->_socket, fd_count, fd_size);
        std::cout << "pollserver: new connection from " << this->_host << " on socket " << this->_socket << std::endl;
    }
}