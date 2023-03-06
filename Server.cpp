#include "Server.hpp"

Server::Server(std::string name) : _name(name) {

    memset(this->_svc, 0, NI_MAXSERV);
}

Server::~Server(void) {}

Server::Server(const Server& src) { *this = src; }

int Server::getSocket(void) const {

    return (this->_socket);
}

void    Server::fillSockAddr(int port) {

    this->_sockaddr.sin_family = AF_INET;
    this->_sockaddr.sin_port = port;
    this->_sockaddr.sin_addr.s_addr = INADDR_ANY;
}

void    Server::setSocket(void) {

    this->_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_socket == -1)
        std::cerr << "Can't create socket." << std::endl;
}

void    Server::_bind(void) {

    if (bind(this->_socket, (sockaddr*)&this->_sockaddr, sizeof(this->_sockaddr)) == -1)
        std::cerr << "Can't bind to IP/port." << std::endl;
}

void    Server::_listen(void) {

    if (listen(this->_socket, SOMAXCONN) == -1)
        std::cerr << "Can't listen." << std::endl;
    if (this->_socket == -1)
        std::cerr << "error getting listening socket" << std::endl;
}