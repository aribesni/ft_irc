#ifndef CLIENT_H
# define CLIENT_H

# include <iostream>
#include <sstream>
# include <netdb.h>
# include <string>
# include "Server.hpp"
#include <stdlib.h>

class Server;
class Client {

    public :
        // Constructor Destructor
        Client(void);
        ~Client(void);
        Client(Server *server);//@ran_add

        // Getters
        int         getSocket(void) const;
        std::string getNick(void) const;
        std::string getUser(void) const;
        std::string getPrefix(void) const;
        bool        getRegistrationStatus (void) const;
        Server      *getServer(void) const;//@ran_add
        std::string getPassword(void) const;
        std::string getPass(void) const;

        // Setters
        void        setSocket(int socket);
        int         setNick(std::string &nickname);
        void        setUsr(std::string &usrname);
        void        setPass(std::string &pass); 
        void        setPassword(std::string &password); 
        void        setHostname(std::string &hostname);
        void        setAsRegistered(void);
        void        setPrefix(void);

        std::string creatNickname(void);

        // int         _init();
        sockaddr_in _sockaddr;
        socklen_t   _socklen;

    private :
        Server      *_server; //@ran_add
        std::string _password;//server password
        int         _socket;
        char        _host[NI_MAXHOST];
        bool        _isRegistered;
        std::string _prefix;
        std::string _hostname;
        std::string _user;
        std::string _nick;
        std::string _pass;
        std::string _msgWelcome;
        
};

#endif