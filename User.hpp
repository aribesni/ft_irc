#ifndef USER_H
# define USER_H

# include <iostream>
# include "Client.hpp"
# include "Server.hpp"
# include "Message.hpp"
# include <string>
# include "utils.hpp"

# define BUFFER_SIZE 4096
class User {

    public :

        User(void);
        ~User(void);

        int     getSocket(void) const;
        void    _accept(Client *client, Server *server, int *fd_count, int *fd_size);
        int     _init();
        void    setNick(std::string &nickname);
        void    setUsr(std::string &usrname);


    private :
        
        int         _socket;
        char        _host[NI_MAXHOST];
        sockaddr_in _sockaddr;
        socklen_t   _socklen;
        std::string _prefix;
        std::string _user;
        std::string _nick;
        std::string _pass;
        std::string _msgWelcome;
        
};

#endif