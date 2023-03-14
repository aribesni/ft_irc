#include "Server.hpp"

Server::Server(std::string name) : _name(name)
{
    this->_pollfds = std::vector<pollfd>(1);
// TO DO: change memset function with c++ equivalent
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

void    Server::_accept(Client & client) {
// Accept the connection and return new client socket
    int newsocket;
    newsocket = accept(this->getSocket(), (sockaddr *)&client._sockaddr, &client._socklen);
    client.setSocket(newsocket);
    std::cout << "new Client " << inet_ntoa(client._sockaddr.sin_addr) << ":" << ntohs(client._sockaddr.sin_port) << " (" << client.getSocket() << ")" << std::endl;
}

std::string     Server::getPassword(void) const
{
    return (this->_password);
}

void Server::acceptNewConnection()
{
    Client  client;
    Replies replies;
    this->_accept(client);
    struct pollfd newpollfd;
    newpollfd.fd = client.getSocket();
    newpollfd.events = POLLIN;
    this->_pollfds.push_back(newpollfd);
    this->clients[newpollfd.fd] = client;
    send(client.getSocket(), replies.RPL_WELCOME("001").data(), replies.RPL_WELCOME("001").size(), 0);
}

void Server::handleClientRequest(Client & client)
{
    // Handle client registration
    // if (client.getRegistrationStatus() == false)
    // {
        // 1. Parse registration messages and get client nick, user and password
            // 1.1 Loop on buffer. When buffer finds \r\n>> create Message, handles Message, then empty buffer and go on with loop
            // 1.1.1 PASS > check if password is correct. if not skip the rest
            // 1.1.2 USER > check if user format is correct. if not skip the rest
            // 1.1.3 NICK > check if nick format is correct and if nick is not already used (ERR_NICKNAMEINUSE). If it is, register user (isRegistered = true). If not ???
        // 2- If correct registration, server sends block of welcome message
            // send(this->getSocket(), this->_replies.RPL_WELCOME("001").data(), this->_replies.RPL_WELCOME("001").size(), 0);
            // send(this->getSocket(), this->_replies.RPL_YOURHOST("002").data(), this->_replies.RPL_YOURHOST("002").size(), 0);
            // send(this->getSocket(), this->_replies.RPL_CREATED("003").data(), this->_replies.RPL_CREATED("003").size(), 0);
            // send(this->getSocket(), this->_replies.RPL_MYINFO("004").data(), this->_replies.RPL_MYINFO("004").size() - 1, 0);
            // send(this->getSocket(), this->_replies.RPL_MOTD("372").data(), this->_replies.RPL_MOTD("372").size(), 0);
            // send(this->getSocket(), this->_replies.RPL_MOTDSTART("375").data(), this->_replies.RPL_MOTDSTART("375").size(), 0);
            // send(this->getSocket(), this->_replies.RPL_ENDOFMOTD("376").data(), this->_replies.RPL_ENDOFMOTD("376").size(), 0);
        char buf[BUFFER_SIZE];
        int nbytes = recv(client.getSocket(), buf, sizeof(buf), 0);
        // std::cout << "my buf" << buf << std::endl;
        // client.setAsRegistered();
        if (nbytes <= 0)
        {
            // Got error or connection closed by client
            if (nbytes == 0)
                std::cout << "pollserver: socket " << client.getSocket() << " hung up" << std::endl;
            else
                perror("recv");
            close(client.getSocket()); // Bye!
        }
    // }
    else //if (client.getRegistrationStatus() == true)
    {
        // Handle other requests
        // WIP
        // ssize_t buff_size;
        // char buf[BUFFER_SIZE];
        // Loop on buff till we get a end of message delimiter /r/n
        // buff_size = recv(client.getSocket(), buf, sizeof(buf), 0);
        // std::cout << "buff size" << buff_size << std::endl;
        // buf[buff_size] = 0;
        // std::cout << "my buf" << buf << std::endl;
        // PRIVATE MESSAGE
        std::map<int, Client>::iterator     _it;
        for (_it = this->clients.begin(); _it != this->clients.end(); _it++)
        {
            if (_it->first == client.getSocket())
                continue ;
            if (send(_it->first, buf, nbytes, 0) == -1)
                perror("send");
        }
    }
}
