#include "Client.hpp"

Client::Client(void) : _isRegistered(false) {
// TO DO: Change memset to a c++ method/func
    memset(this->_host, 0, NI_MAXHOST);
    this->_socklen = sizeof(this->_sockaddr);
}
Client::Client(Server *server) : _server(server), _isRegistered(false){
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

bool Client::getRegistrationStatus(void) const
{
    return (this->_isRegistered);
}

//setter


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
    Replies replies;
    if (nickname.size() > 9){
        send(getSocket(), replies.ERR_ERRONEUSNICKNAME("432").data(), replies.ERR_ERRONEUSNICKNAME("432").size(), 0);
        _nick = creatNickname();
        return;
    }
    std::map<int, Client>::iterator     it;
    for (it = _server->clients.begin(); it != _server->clients.end(); it++)
    {
        if (it->first == getSocket()) // don't send message to client's own fd
            continue ;
        if (nickname == it->second._nick){
            send(getSocket(), replies.ERR_NICKNAMEINUSE("433").data(), replies.ERR_NICKNAMEINUSE("433").size(), 0);
            _nick = creatNickname();
            return;
        }
    }
    
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

void Client::setPassword(std::string &password){
    _password = password;
}

bool Client::checkRegisCondition(){
    Replies replies;
    if(_pass.empty() || _nick.empty() || _user.empty()){
        std::cout << "empty 461\n";
        send(getSocket(), replies.ERR_NEEDMOREPARAMS("461").data(), replies.ERR_NEEDMOREPARAMS("461").size(), 0);
        return (false);
    }
    if(_pass != _password){
        std::cout << "wrong password\n";
        return(false);
    }
    return (true);
}

std::string creatNickname(void){
    static int nb;
    std::ostringstream oOStrStream;
    oOStrStream << nb;
    
    std::string name = "Guest" + oOStrStream.str();
    nb++;
    std::cout << "creatname " << name << std::cout;
    return(name);
}