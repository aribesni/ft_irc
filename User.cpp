#include "User.hpp"

User::User(void) {

    memset(this->_host, 0, NI_MAXHOST);
    this->_socklen = sizeof(this->_sockaddr);
}

User::~User(void) {}

int User::getSocket(void) const {
    return (this->_socket);
}

void    User::_accept(Client *client, Server *server, int *fd_count, int *fd_size) {

    this->_socket = accept(server->getSocket(), (sockaddr *)&this->_sockaddr, &this->_socklen);
        if(!_init()){
            send(this->getSocket(), _msgWelcome.c_str(), _msgWelcome.size() +1, 0);
            if (this->getSocket() == -1)
                perror("accept");
            else
            {
                client->add_to_pfds(this->_socket, fd_count, fd_size);
                std::cout << "pollserver: new connection from " << this->_host << " on socket " << this->_socket << std::endl;
            }
       }   
}

int  User::_init(){
        char buf[BUFFER_SIZE];
        memset(buf, 0, BUFFER_SIZE);
        sleep(2);
        recv(this->getSocket(), buf, sizeof(buf), 0);
        Message msg(buf);
        msg.parsingCMD_init();
        if(msg._pass != "password"){
             std::cout << "wrong password!\n" ;// ?need to send one message to clean?
             return (1); 
        }    
        _nick=msg.getNick();
        _user=msg.getUser();
        _prefix=msg.getPrefix();
        _msgWelcome = ":" + _prefix + " 001 " + _nick + " :Welcome to the IRC__ Network, " + _prefix + "\n";
        return(0);
}

void  User::setNick(std::string &nickname){
    _nick = nickname;
}


void  User::setUsr(std::string &usrname){
    _user = usrname;
}