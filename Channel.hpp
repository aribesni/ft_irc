#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include "Client.hpp"
# include <vector>

class Channel
{

	public:
		// CONSTRUCTOR / DESTRUCTOR
		Channel();
		Channel(std::string chanName, Client * client);
		Channel( Channel const & src );
		~Channel();
		// GETTERS
		std::string				getName(void) const;
		std::vector<Client* >	getListOfClients(void) const;

		// SETTERS
		void					addAClient(Client * client);
		Channel &		operator=( Channel const & rhs );

	private:
		std::string				_name;
		std::vector<Client*>	_listOfClients;


};

#endif /* ********************************************************* CHANNEL_H */