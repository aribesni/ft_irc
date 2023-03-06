#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <string>
# include <iostream>
# include <arpa/inet.h>

class Server {

    public :

        Server(std::string name);
        Server(const Server& src);
        ~Server(void);

        int     getSocket(void) const;
        void    fillSockAddr(int port);
        void    setSocket(void);
        void    _bind(void);
        void    _listen(void);

    private :

        int         _socket;
        std::string _name;
        char        _svc[NI_MAXSERV];
        sockaddr_in _sockaddr;
};

#endif