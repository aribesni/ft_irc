#include "Client.hpp"

Client  pollgetClientWithFd(struct pollfd)
{
	// loop on all client sockets
	std::vector<Client>::iterator it;
	for (it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		if ((*it).getSocket() == targetpollfd.fd)
			return (*it);
	}
	return (*it);
}