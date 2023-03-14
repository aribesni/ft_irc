#ifndef CLIENT_H
# define CLIENT_H

# include <iostream>
# include <netdb.h>

class Client {

    public :

        Client(void);
        ~Client(void);

        int     getSocket(void) const;
        void    setSocket(int socket);
        bool    getRegistrationStatus (void) const;
        sockaddr_in _sockaddr;
        socklen_t   _socklen;

    private :
        std::string _password;
        int         _socket;
        char        _host[NI_MAXHOST];
        std::string _nick;
        bool        _isRegistered;
};

#endif