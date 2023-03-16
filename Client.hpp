#ifndef CLIENT_H
# define CLIENT_H

# include <iostream>
#include <sstream>
# include <netdb.h>
# include <string.h>
# include "Replies.hpp"
# include "Server.hpp"

class Server;
class Client {

    public :
        // Constructor Destructor
        Client(void);
        Client(Server *server);
        ~Client(void);


        // Getters
        int         getSocket(void) const;
        std::string getNick(void) const;
        bool        getRegistrationStatus (void) const;

        // Setters
        void        setPassword(std::string &password);//this is server password
        void        setSocket(int socket);
        void        setNick(std::string &nickname);
        void        setUsr(std::string &usrname);
        void        setPass(std::string &pass);// this is client password;
        void        setHostname(std::string &hostname);
        void        setAsRegistered(void);
        void        setPrefix(void);

        //memberfunction
        bool        checkRegisCondition(void);

        // int         _init();
        sockaddr_in _sockaddr;
        socklen_t   _socklen;

    private :
        Server         *_server;
        std::string _password;
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

std::string creatNickname(void);

#endif