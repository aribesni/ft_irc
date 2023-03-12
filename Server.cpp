#include "Server.hpp"

Server::Server(std::string name, int max_clients) : _name(name) {
    this->_pollfds = std::vector<pollfd>(max_clients);
    memset(this->_svc, 0, NI_MAXSERV);
}

Server::~Server(void) {}

Server::Server(const Server& src) { *this = src; }

int Server::getSocket(void) const {

    return (this->_socket);
}

void    Server::fillServerPollfd(void) {
    this->_pollfds[0].fd = this->_socket;
    this->_pollfds[0].events = POLLIN;
}

void    Server::createSocket(void) {

    this->_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_socket == -1)
        std::cerr << "Can't create socket." << std::endl;
}

void    Server::_bind(sockaddr_in hint) {

    if (bind(this->_socket, (sockaddr*)&hint, sizeof(hint)) == -1)
        std::cerr << "Can't bind to IP/port." << std::endl;
}

void    Server::_listen(void) {

    if (listen(this->_socket, SOMAXCONN) == -1)
        std::cerr << "Can't listen." << std::endl;
    if (this->_socket == -1)
        std::cerr << "error getting listening socket" << std::endl;
}