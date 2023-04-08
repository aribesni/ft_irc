#include "Channel.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel()
{
}

Channel::Channel(Channel const & src)
{
	*this = src;
}

Channel::Channel(std::string chanName, Client * client, std::string chanmode) : _name(chanName)
{
	_clientsMap[client] = chanmode;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/


/*
** --------------------------------- METHODS ----------------------------------
*/

void	Channel::addClient(Client * client, std::string chanmode)
{
	_clientsMap[client] = chanmode;
}

void	Channel::removeClient(Client * client)
{
	_clientsMap.erase(client);
}

/*
** --------------------------------- SETTERS ---------------------------------
*/



/*
** --------------------------------- GETTERS ---------------------------------
*/

std::map<Client*, std::string>&	Channel::getClientsMap(void)
{
	return (_clientsMap);
}

std::string				Channel::getName(void) const
{
	return (_name);
}
/* ************************************************************************** */