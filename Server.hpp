#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <netdb.h>
# include <vector>
# include <poll.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <string>
# include <iostream>
# include <arpa/inet.h>
# include <cstdio>


class Server {

    public :

        Server(std::string name);
        Server(const Server& src);
        ~Server(void);

        int     getSocket(void) const;
        void    fillServerPollfd(void);
        void    createSocket(void);
        void    _bind(sockaddr_in bind);
        void    _listen(void);
        std::vector<struct pollfd>  _pollfds;
        void    _acceptNewConnection();
        void    _handleClientRequest(int fd);
        std::vector<Client>  clients;
        // Client & fd_to_client(int fd);

    private :

        int                         _socket;
        std::string                 _name;
        char                        _svc[NI_MAXSERV];
};

#endif