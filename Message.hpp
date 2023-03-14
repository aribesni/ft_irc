#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>
# include <vector>

class Message
{
	public:
		std::string					prefix;
		std::string             	cmd;
		std::vector<std::string>    paramList;
};

#endif