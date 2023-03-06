#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <netdb.h>
# include <poll.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <string>
# include <iostream>
# include <vector>
# include "Server.hpp"

class Client {

    public :
        
        Client(int fd_size);
        Client(const Client& src);
        ~Client(void);

        int     getSocket(void) const;
        pollfd  getPfd(int i) const;
        void    fillpfds(Server *server);
        int     _poll(void);
        void    _accept(Server *server, int *fd_count, int *fd_size);
        void    del_from_pfds(int i, int *fd_count);

    private :

        // int         _port;
        int         _socket;
        char        _host[NI_MAXHOST];
        std::string _nick;
        sockaddr_in _sockaddr;
        socklen_t   _socklen;
        std::vector<struct pollfd>  _pfds;
};

#endif