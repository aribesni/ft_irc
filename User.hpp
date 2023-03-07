#ifndef USER_H
# define USER_H

# include <iostream>
# include "Client.hpp"
# include "Server.hpp"

class User {

    public :

        User(void);
        ~User(void);

        int     getSocket(void) const;
        void    _accept(Client *client, Server *server, int *fd_count, int *fd_size);


    private :
        
        int         _socket;
        char        _host[NI_MAXHOST];
        std::string _nick;
        sockaddr_in _sockaddr;
        socklen_t   _socklen;
};

#endif