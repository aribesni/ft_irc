#include "User.hpp"

User::User(void) {}

User::User(int fd, std::string nick) : _fd(fd), _nick(nick) {

    std::cout << "fd : " << this->_fd << std::endl;
    std::cout << "nickname : " << this->_nick << std::endl;
}

User::~User(void) {}