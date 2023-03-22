#ifndef SERVER_H
# define SERVER_H
# define BUFFER_SIZE 4096
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <vector>
# include <map>
# include <poll.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <string>
# include <arpa/inet.h>
# include <cstdio>
# include "Client.hpp"
# include "Replies.hpp"
# include "bufferParser.hpp"
# include "Message.hpp"
# include "Channel.hpp"

class Server {

    public :

        Server(std::string name);
        Server(const Server& src);
        ~Server(void);

        int     getSocket(void) const;
        void    fillServerPollfd(void);
        void    createSocket(void);
        void    _bind(sockaddr_in bind);
        void    _accept(Client & client);
        void    _listen(void);
        std::vector<struct pollfd>  _pollfds;
        void    acceptNewClient();
        void    handleClientRequest(Client & client);
        // std::vector<Client>  clients;
        std::map<int, Client>  clients;
        // Client &        getClientWithFd(int fd);
        std::string     getPassword(void) const;

    private :
        std::string                     _password;
        int                             _socket;
        std::string                     _name;
        char                            _svc[NI_MAXSERV];
        std::map<std::string, Channel>  _channels; /* channelName, Channel object*/
};

#endif