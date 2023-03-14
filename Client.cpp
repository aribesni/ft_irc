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

bool Client::getRegistrationStatus(void) const
{
    return (this->_isRegistered);
}

void Client::setSocket(int socket)
{
    this->_socket = socket;
}

// int  Client::_init(){
//         //recv pass nick user
//         char buf[BUFFER_SIZE];
//         memset(buf, 0, BUFFER_SIZE);
//         sleep(1);
//         recv(this->getSocket(), buf, sizeof(buf), 0);
//         BufferParser msg(buf);
//         // parsing and save info in user
//         msg.parsingCMD_init(*this);
//         if(_pass != "password"){
//              std::cout << "wrong password!\n" ;// ?need to send one message to clean?
//              return(1); // here should send RPL:462
//         }
//         _prefix = _nick + "!" + _user + "@" + _hostname;
//         _msgWelcome = ":" + _prefix + " 001 " + _nick + " :Welcome to the IRC__ Network, " + _prefix + "\n";
//         return(0);
// }

void  Client::setNick(std::string &nickname){
    _nick = nickname;
}

void  Client::setAsRegistered(void){
    _isRegistered = true;
}

void  Client::setUsr(std::string &usrname){
    _user = usrname;
}

void  Client::setPass(std::string &pass){
    _pass = pass;
}

void  Client::setHostname(std::string &hostname){
    _hostname = hostname;
}