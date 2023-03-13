#include "Client.hpp"

Client  pollfd_to_client(struct pollfd)
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