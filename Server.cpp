#include "Server.hpp"

Server::Server(std::string name) : _name(name) {
    this->_pollfds = std::vector<pollfd>(1);
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

Client & Server::fd_to_client(int fd)
{
    // loop on all client sockets
    std::vector<Client>::iterator it;
    for (it = this->clients.begin(); it != this->clients.end(); ++it)
    {
        if ((*it).getSocket() == fd)
            return (*it);
    }
    return (*it);
}

void    Server::_accept(Client & client) {
// Accept the connection and return new client socker
    int newsocket;
    newsocket = accept(this->getSocket(), (sockaddr *)&client._sockaddr, &client._socklen);
    client.setSocket(newsocket);
    std::cout << "new Client " << inet_ntoa(client._sockaddr.sin_addr) << ":" << ntohs(client._sockaddr.sin_port) << " (" << client.getSocket() << ")" << std::endl;
    // send(this->getSocket(), ":server 001 <my_nick>\n", sizeof("my_nick\n"), 0);

    // send(this->getSocket(), ":server 001 <test> :Welcome to the <network> Network, <test>[!<client>@<host>]\n", 78, 0);
    // if (this->getSocket() == -1)
        // perror("accept");
}

std::string     Server::getPassword(void) const
{
    return (this->_password);
}