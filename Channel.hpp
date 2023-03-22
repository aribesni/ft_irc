#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include "Client.hpp"
# include <vector>

class Channel
{

	public:

		Channel();
		// Channel( Channel const & src );
		~Channel();

		// Channel &		operator=( Channel const & rhs );

	private:
		std::string			_name;
		std::vector<Client>	_listOfClients;


};

#endif /* ********************************************************* CHANNEL_H */