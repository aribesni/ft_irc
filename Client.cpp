#include "Client.hpp"

Client::Client(void) : _isRegistered(false) {
// TO DO: Change memset to a c++ method/func
    memset(this->_host, 0, NI_MAXHOST);
    this->_socklen = sizeof(this->_sockaddr);
}

Client::~Client(void) {}

int Client::getSocket(void) const
{
    return (this->_socket);
}

std::string Client::getNick(void) const {

    return (this->_nick);
}

std::string Client::getUser(void) const {

    return (this->_user);
}

std::string Client::getPrefix(void) const {

    return (this->_prefix);
}

bool Client::getRegistrationStatus(void) const
{
    return (this->_isRegistered);
}

void Client::setSocket(int socket)
{
    this->_socket = socket;
}

void  Client::setPrefix(void){
        _prefix = _nick + "!" + _user + "@" + _hostname;
//      _msgWelcome = ":" + _prefix + " 001 " + _nick + " :Welcome to the IRC__ Network, " + _prefix + "\n";
       // std::cout << "test_setprefic: "<<_prefix << std::endl;
 }

void  Client::setNick(std::string &nickname){
    _nick = nickname;
    //std::cout << "test_nick: " << _nick << std::endl;
}

void  Client::setAsRegistered(void){
    _isRegistered = true;
}

void  Client::setUsr(std::string &usrname){
    _user = usrname;
    //std::cout << "test_user: " << _user<< std::endl;
}

void  Client::setPass(std::string &pass){
    _pass = pass;
    //std::cout << "test_pass: " << _pass << std::endl;
}

void  Client::setHostname(std::string &hostname){
    _hostname = hostname;
    //std::cout << "test_pass: " << _hostname << std::endl;
}