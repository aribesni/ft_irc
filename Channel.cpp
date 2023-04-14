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

Channel::Channel(std::string chanName, Client * client, std::string userchanmode) : _name(chanName), _mode(""), _modeArguments("")
{
	_clientsMap[client] = userchanmode;
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

void	Channel::addModeArguments(std::string modeArguments)
{
	if (_modeArguments == "")
		_modeArguments = modeArguments;
	else
		_modeArguments.append(" " + modeArguments);
}


/*
** --------------------------------- SETTERS ---------------------------------
*/

void								Channel::setMode(std::string mode)
{
	_mode = mode;
}

/*
** --------------------------------- GETTERS ---------------------------------
*/

std::map<Client*, std::string>&	Channel::getClientsMap(void)
{
	return (_clientsMap);
}

std::string const &				Channel::getName(void) const
{
	return (_name);
}

std::string const &				Channel::getMode(void) const
{
	return (_mode);
}

std::string const &				Channel::getModeArguments(void) const
{
	return (_modeArguments);
}

/* ************************************************************************** */