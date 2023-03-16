#ifndef CLIENT_H
# define CLIENT_H

# include <iostream>
# include <netdb.h>
# include <string.h>

class Client {

    public :
        // Constructor Destructor
        Client(void);
        ~Client(void);

        // Getters
        int         getSocket(void) const;
        std::string getNick(void) const;
        std::string getUser(void) const;
        std::string getPrefix(void) const;
        bool        getRegistrationStatus (void) const;

        // Setters
        void        setSocket(int socket);
        void        setNick(std::string &nickname);
        void        setUsr(std::string &usrname);
        void        setPass(std::string &pass);
        void        setHostname(std::string &hostname);
        void        setAsRegistered(void);
        void        setPrefix(void);
        // int         _init();
        sockaddr_in _sockaddr;
        socklen_t   _socklen;

    private :
        std::string _password;
        int         _socket;
        char        _host[NI_MAXHOST];
        bool        _isRegistered;
        std::string _prefix;
        std::string _hostname;
        std::string _user;
        std::string _nick;
        std::string _pass;
        std::string _msgWelcome;
};

#endif