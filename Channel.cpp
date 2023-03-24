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

Channel::Channel(std::string chanName, Client * client) : _name(chanName)
{
	_listOfClients.push_back(client);
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

Channel &		Channel::operator=( Channel const & rhs )
{
	_listOfClients = rhs.getListOfClients();
	_name = rhs.getName();
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- SETTERS ---------------------------------
*/

void	Channel::addAClient(Client * client)
{
	_listOfClients.push_back(client);
}

/*
** --------------------------------- GETTERS ---------------------------------
*/

std::vector<Client*>	Channel::getListOfClients(void) const
{
	return (_listOfClients);
}

std::string				Channel::getName(void) const
{
	return (_name);
}
/* ************************************************************************** */