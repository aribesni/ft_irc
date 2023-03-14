#ifndef CLIENT_H
# define CLIENT_H

# include <iostream>
# include <netdb.h>

class Client {

    public :
        // Constructor Destructor
        Client(void);
        ~Client(void);

        // Getters
        int         getSocket(void) const;
        bool        getRegistrationStatus (void) const;
        
        // Setters
        void        setSocket(int socket);

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