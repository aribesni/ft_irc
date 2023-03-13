#ifndef CLIENT_H
# define CLIENT_H

# include <iostream>
# include "Server.hpp"

class Client {

    public :

        Client(void);
        ~Client(void);

        int     getSocket(void) const;
        void    _accept(Server *server);


    private :

        int         _socket;
        char        _host[NI_MAXHOST];
        std::string _nick;
        sockaddr_in _sockaddr;
        socklen_t   _socklen;
};

#endif