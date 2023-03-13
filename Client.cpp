#include "Client.hpp"

Client::Client(void) {

    memset(this->_host, 0, NI_MAXHOST);
    this->_socklen = sizeof(this->_sockaddr);
}

Client::~Client(void) {}

int Client::getSocket(void) const {

    return (this->_socket);
}

void    Client::_accept(Server *server) {
// Accept the connection and return new client socker
    this->_socket = accept(server->getSocket(), (sockaddr *)&this->_sockaddr, &this->_socklen);
    std::cout << "new Client " << inet_ntoa(this->_sockaddr.sin_addr) << ":" << ntohs(this->_sockaddr.sin_port) << " (" << this->_socket << ")" << std::endl;
    // send(this->getSocket(), ":server 001 <my_nick>\n", sizeof("my_nick\n"), 0);

    // send(this->getSocket(), ":server 001 <test> :Welcome to the <network> Network, <test>[!<client>@<host>]\n", 78, 0);
    // if (this->getSocket() == -1)
        // perror("accept");
}