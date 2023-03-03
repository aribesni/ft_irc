#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <string>
# include <iostream>
# include <arpa/inet.h>

class Client {

    public :

        Client(void);
        Client(const Client& src);
        ~Client(void);

    // private :

        int         _port;
        int         _socket;
        char        _host[NI_MAXHOST];
        std::string _nick;
        sockaddr_in _sockaddr;
        socklen_t   _socklen;
};

#endif