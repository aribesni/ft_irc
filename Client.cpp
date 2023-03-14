#include "Client.hpp"

Client::Client(void) {
// TO DO: Change memset to a c++ method/func
    memset(this->_host, 0, NI_MAXHOST);
    this->_socklen = sizeof(this->_sockaddr);
}

Client::~Client(void) {}

int Client::getSocket(void) const
{
    return (this->_socket);
}

bool Client::getRegistrationStatus(void) const
{
    return (this->_isRegistered);
}

void Client::setSocket(int socket)
{
    this->_socket = socket;
}

