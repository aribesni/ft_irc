#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include "Client.hpp"
# include <map>
# include <algorithm>

class Channel
{

	public:
		// CONSTRUCTOR / DESTRUCTOR
		Channel();
		Channel(std::string chanName, Client * client, std::string chanmode);
		Channel( Channel const & src );
		~Channel();

		// OVERLOADS

		// GETTERS
		std::string							getName(void) const;
		std::map<Client*, std::string>&		getClientsMap(void);

		// METHODS
		void								addClient(Client * client, std::string chanmode);
		void								removeClient(Client * client);

	private:
		std::string							_name;
		std::map<Client*, std::string>		_clientsMap; /* map of client and chan mode*/
};

// b <mask>: Adds or removes a ban; a ban will prevent a user who matches the given mask from joining the channel unless he or she is invited or in the exempt list.
// e <mask>: Adds or removes a ban exception; users who match a mask on the exempt list are able to join a channel even if they also match an entry on the ban list.
// i: When enabled, users need to be invited into the channel or have a matching entry in the invite list.
// I <mask>: Adds or removes an invite; users who match a mask on the invite list are able to join even if the channel is set to invite only.
// k <key>: Adds or removes a channel key, aka a password; users will not be able to join the channel without providing the key.
// l <count>: Adds, removes or updates the maximum amount of users that may join the channel.
// m: When enabled, users who are not opped or voiced cannot send messages to the channel.
// n: When enabled, users who are not on the channel cannot send messages to it.
// p: When enabled, the channel will not be displayed in your WHOIS output.
// s: When enabled, the channel will not be displayed in the LIST output.
// t: When enabled, users who are not opped or voices cannot modify the channel topic.
// o <nickname>: Adds or removes the operator status from a nickname.
// v <nickname>: Adds or removes the voice status from a nickname.

        // void        setChanMode(std::string mode);
// std::string Client::getChanMode(void) const {return (this->_chan_mode);}
#endif /* ********************************************************* CHANNEL_H */