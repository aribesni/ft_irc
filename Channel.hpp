#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include "Client.hpp"
# include <vector>
# include <algorithm>

class Channel
{

	public:
		// CONSTRUCTOR / DESTRUCTOR
		Channel();
		Channel(std::string chanName, Client * client);
		Channel( Channel const & src );
		~Channel();

		// OVERLOADS
		Channel &		operator=( Channel const & rhs );

		// GETTERS
		std::string				getName(void) const;
		std::vector<Client* >	getListOfClients(void) const;

		// METHODS
		void					addClient(Client * client);
		void					removeClient(Client * client);

	private:
		std::string				_name;
		std::vector<Client*>	_listOfClients;


};

#endif /* ********************************************************* CHANNEL_H */