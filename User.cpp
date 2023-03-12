#include "User.hpp"

User::User(void) {

    memset(this->_host, 0, NI_MAXHOST);
    this->_socklen = sizeof(this->_sockaddr);
}

User::~User(void) {}

int User::getSocket(void) const {

    return (this->_socket);
}

void    User::_accept(Server *server) {
// Accept the connection and return new client socker
    this->_socket = accept(server->getSocket(), (sockaddr *)&this->_sockaddr, &this->_socklen);
    // send(this->getSocket(), ":server 001 <my_nick>\n", sizeof("my_nick\n"), 0);

    // send(this->getSocket(), ":server 001 <test> :Welcome to the <network> Network, <test>[!<user>@<host>]\n", 78, 0);
    // if (this->getSocket() == -1)
        // perror("accept");
}