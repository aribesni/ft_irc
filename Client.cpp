#include "Client.hpp"

Client::Client(int fd_size) {

    this->_pfds = std::vector<pollfd>(fd_size);
}

Client::~Client(void) {}

Client::Client(const Client& src) { *this = src; }

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

void    Client::add_to_pfds(int newfd, int *fd_count, int *fd_size)
{
    // If we don't have room, add more space in the pfds array
    if (*fd_count == *fd_size) {
        *fd_size *= 2;
        this->_pfds.resize(*fd_size);
    }
    this->_pfds[*fd_count].fd = newfd;
    this->_pfds[*fd_count].events = POLLIN;
    (*fd_count)++;
}

void    Client::del_from_pfds(int i, int *fd_count) {
    
    this->_pfds[i] = this->_pfds[*fd_count - 1];
    (*fd_count)--;
}