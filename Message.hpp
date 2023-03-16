#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>
# include <vector>
#include "Client.hpp"

class	Client;
class Message
{
	public:
		Message(void);
		Message(std::vector<std::string> &tokens);
		~Message(void);
		

		std::string 				getCMD(void);
		std::vector<std::string>	getParams(void);
		void						execCMD(Client &client);

	private:
		std::string					_prefix;
		std::string             	_cmd;
		std::vector<std::string>    _params;

};

#endif