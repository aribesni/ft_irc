#ifndef USER_H
# define USER_H

# include <iostream>

class User {

    public :

        User(void);
        User(int fd, std::string nick);
        ~User(void);

    private :
        
        int         _fd;
        std::string _nick;
};

#endif