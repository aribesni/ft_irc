#ifndef REPLIES_H
# define REPLIES_H

# include <iostream>
# include "Client.hpp"

	class Replies {

		public :

			Replies(Client &client)
			{
				setVariables(&client);
			}
			~Replies(void) {};

			void	setVariables(Client *client) {

				this->_network = "Internet Relay";
				this->_nickname = client->getNick();
				this->_user = client->getUser();
				this->_host = "localhost";
				this->_server = "Ircserv";
				this->_channel = "<channel>";
				this->_date_time = "Tue March 14 at 12:05";
				this->_version = "1.0";
				this->_mode = client->getMode();
				this->_prefix = client->getPrefix();
			}

			void	sendMotd(int client_socket) {

				std::string motd1 = "Welcome to our Ircserv IRC Network !\r\n";
				std::string motd2 = "For any inquiries please refer to aribesni@student.42.fr, gduchate@student.42.fr or rliu@student.42.fr.\r\n";
				std::string motd3 = "Enjoy your time here.\r\n";
				send(client_socket, this->RPL_MOTD("372", "\r\n").data(), this->RPL_MOTD("372", "\r\n").size(), 0);
				send(client_socket, this->RPL_MOTD("372", "\r\n").data(), this->RPL_MOTD("372", "\r\n").size(), 0);
				send(client_socket, this->RPL_MOTD("372", motd1).data(), this->RPL_MOTD("372", motd1).size(), 0);
				send(client_socket, this->RPL_MOTD("372", "\r\n").data(), this->RPL_MOTD("372", "\r\n").size(), 0);
				send(client_socket, this->RPL_MOTD("372", motd2).data(), this->RPL_MOTD("372", motd2).size(), 0);
				send(client_socket, this->RPL_MOTD("372", "\r\n").data(), this->RPL_MOTD("372", "\r\n").size(), 0);
				send(client_socket, this->RPL_MOTD("372", motd3).data(), this->RPL_MOTD("372", motd3).size(), 0);
				send(client_socket, this->RPL_MOTD("372", "\r\n").data(), this->RPL_MOTD("372", "\r\n").size(), 0);
				send(client_socket, this->RPL_MOTD("372", "\r\n").data(), this->RPL_MOTD("372", "\r\n").size(), 0);
			}

			/* "001" */ std::string RPL_WELCOME(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":Welcome to the " + this->_network + " Network, " + this->_prefix + "\r\n"); };
			/* "002" */ std::string RPL_YOURHOST(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":Your host is " + this->_server + ", running version " + this->_version + "\r\n"); };
			/* "003" */ std::string RPL_CREATED(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":This server was created " + this->_date_time + "\r\n"); };
			/* "004" */ std::string RPL_MYINFO(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_server + " " + this->_version + " <user_modes> <chan_modes>" + "\r\n"); };
			/* "005" */ std::string RPL_BOUNCE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_server + " " + this->_version + " <user_modes> <chan_modes> <channel_modes_with_params> <user_modes_with_params> <server_modes> <server_modes_with_params>" + "\r\n"); };
			/* "043" */ std::string RPL_SAVENICK(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<info>" + "\r\n"); };
			/* "200" */ std::string RPL_TRACELINK(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "Link " + this->_version + "[.<debug_level>] <destination> <next_server> [V<protocol_version> <link_uptime_in_seconds> <backstream_sendq> <upstream_sendq>]" + "\r\n"); };
			/* "201" */ std::string RPL_TRACECONNECTING(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "Try. <class> " + this->_server + "\r\n"); };
			/* "202" */ std::string RPL_TRACEHANDSHAKE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "H.S. <class> " + this->_server + "\r\n"); };
			/* "203" */ std::string RPL_TRACEUNKNOWN(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "???? <class> [<connection_address>]" + "\r\n"); };
			/* "204" */ std::string RPL_TRACEOPERATOR(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "Oper <class> " + this->_nickname + "\r\n"); };
			/* "205" */ std::string RPL_TRACEUSER(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "Client <class> " + this->_nickname + "\r\n"); };
			/* "206" */ std::string RPL_TRACESERVER(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "Serv <class> <int>S <int>C " + this->_server + " <nick!user|*!*>@<host|server> [V<protocol_version>]" + "\r\n"); };
			/* "207" */ std::string RPL_TRACESERVICE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "Service <class> <name> <type> <active_type>" + "\r\n"); };
			/* "208" */ std::string RPL_TRACENEWTYPE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<newtype> 0 <client_name>" + "\r\n"); };
			/* "209" */ std::string RPL_TRACECLASS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "Class <class> <count>" + "\r\n"); };
			/* "211" */ std::string RPL_STATSLINKINFO(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<linkname> <sendq> <sent_msgs> <sent_bytes> <recvd_msgs> <rcvd_bytes> <time_open>" + "\r\n"); };
			/* "212" */ std::string RPL_STATSCOMMANDS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<command> <count> [<byte_count> <remote_count>]" + "\r\n"); };
			/* "213" */ std::string RPL_STATSCLINE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "C " + this->_host + " * <name> <port> <class>" + "\r\n"); };
			/* "214" */ std::string RPL_STATSNLINE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "N " + this->_host + " * <name> <port> <class>" + "\r\n"); };
			/* "215" */ std::string RPL_STATSILINE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "I " + this->_host + " * " + this->_host + " <port> <class>" + "\r\n"); };
			/* "216" */ std::string RPL_STATSKLINE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "K " + this->_host + " * <username> <port> <class>" + "\r\n"); };
			/* "218" */ std::string RPL_STATSYLINE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "Y <class> <ping_freq> <connect_freq> <max_sendq>" + "\r\n"); };
			/* "219" */ std::string RPL_ENDOFSTATS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<query> :<info>" + "\r\n"); };
			/* "221" */ std::string RPL_UMODEIS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "+" + this->_mode + "\r\n"); };
			/* "234" */ std::string RPL_SERVLIST(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<name> " + this->_server + " <mask> <type> <hopcount> <info>" + "\r\n"); };
			/* "235" */ std::string RPL_SERVLISTEND(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<mask> <type> :<info>" + "\r\n"); };
			/* "241" */ std::string RPL_STATSLLINE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "L <hostmask> * " + this->_server + " <maxdepth>" + "\r\n"); };
			/* "242" */ std::string RPL_STATSUPTIME(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":Server Up <days> days <hours>:<minutes>:<seconds>" + "\r\n"); };
			/* "243" */ std::string RPL_STATSOLINE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "O <hostmask> * " + this->_nickname + " [:<info>]" + "\r\n"); };
			/* "244" */ std::string RPL_STATSHLINE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "H <hostmask> * " + this->_server + "\r\n"); };
			/* "251" */ std::string RPL_LUSERCLIENT(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":There are <int> users and <int> invisible on <int> servers" + "\r\n"); };
			/* "252" */ std::string RPL_LUSEROP(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<int> :<info>" + "\r\n"); };
			/* "253" */ std::string RPL_LUSERUNKNOWN(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<int> :<info>" + "\r\n"); };
			/* "254" */ std::string RPL_LUSERCHANNELS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<int> :<info>" + "\r\n"); };
			/* "255" */ std::string RPL_LUSERME(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":I have <int> clients and <int> servers" + "\r\n"); };
			/* "256" */ std::string RPL_ADMINME(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_server + " :<info>" + "\r\n"); };
			/* "257" */ std::string RPL_ADMINLOC1(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<admin_location>" + "\r\n"); };
			/* "258" */ std::string RPL_ADMINLOC2(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<admin_location>" + "\r\n"); };
			/* "259" */ std::string RPL_ADMINEMAIL(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<email_address>" + "\r\n"); };
			/* "261" */ std::string RPL_TRACELOG(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "File <logfile> <debug_level>" + "\r\n"); };
			/* "262" */ std::string RPL_TRACEEND(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_server + " " + this->_version + "[.<debug_level>] :<info>" + "\r\n"); };
			/* "263" */ std::string RPL_TRYAGAIN(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<command> :<info>" + "\r\n"); };
			/* "301" */ std::string RPL_AWAY(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + " :<message>" + "\r\n"); };
			/* "302" */ std::string RPL_USERHOST(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":*1<reply> *( ' ' <reply> )" + "\r\n"); };
			/* "303" */ std::string RPL_ISON(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":*1" + this->_nickname + " *( ' ' " + this->_nickname + " )" + "\r\n"); };
			/* "305" */ std::string RPL_UNAWAY(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<info>" + "\r\n"); };
			/* "306" */ std::string RPL_NOWAWAY(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<info>" + "\r\n"); };
			/* "311" */ std::string RPL_WHOISUSER(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + this->_user + " " + this->_host + " * :<real_name>" + "\r\n"); };
			/* "312" */ std::string RPL_WHOISSERVER(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname +  " " + this->_server + " :<server_info>" + "\r\n"); };
			/* "313" */ std::string RPL_WHOISOPERATOR(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + " :<privileges>" + "\r\n"); };
			/* "314" */ std::string RPL_WHOWASUSER(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + this->_user + " " + this->_host + " * :<real_name>" + "\r\n"); };
			/* "315" */ std::string RPL_ENDOFWHO(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<name> :<info>" + "\r\n"); };
			/* "317" */ std::string RPL_WHOISIDLE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + " <seconds> :seconds idle" + "\r\n"); };
			/* "318" */ std::string RPL_ENDOFWHOIS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + " :<info>" + "\r\n"); };
			/* "319" */ std::string RPL_WHOISCHANNELS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + " :*( ( '@' / '+' ) " + this->_channel + " ' ' )" + "\r\n"); };
			/* "321" */ std::string RPL_LISTSTART(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "Channels :Clients Name" + "\r\n"); };
			/* "322" */ std::string RPL_LIST(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " <#_visible> :<topic>" + "\r\n"); };
			/* "323" */ std::string RPL_LISTEND(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<info>" + "\r\n"); };
			/* "324" */ std::string RPL_CHANNELMODEIS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " <mode> <mode_params>" + "\r\n"); };
			/* "325" */ std::string RPL_UNIQOPIS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " <nickname>" + "\r\n"); };
			/* "331" */ std::string RPL_NOTOPIC(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<info>" + "\r\n"); };
			/* "332" */ std::string RPL_TOPIC(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<topic>" + "\r\n"); };
			/* "341" */ std::string RPL_INVITING(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + " " + this->_channel + "\r\n"); };
			/* "342" */ std::string RPL_SUMMONING(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_user + " :<info>" + "\r\n"); };
			/* "345" */ std::string RPL_ENDOFREOPLIST(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " <user being invited> <user issuing invite> :<user being invited> has been invited by <user issuing invite>" + "\r\n"); };
			/* "346" */ std::string RPL_INVITELIST(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " <invitemask>" + "\r\n"); };
			/* "347" */ std::string RPL_ENDOFINVITELIST(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<info>" + "\r\n"); };
			/* "348" */ std::string RPL_EXCEPTLIST(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " <exceptionmask>" + "\r\n"); };
			/* "349" */ std::string RPL_ENDOFEXCEPTLIST(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<info>" + "\r\n"); };
			/* "351" */ std::string RPL_VERSION(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_version + "[.<debuglevel>] " + this->_server + " :<comments>" + "\r\n"); };
			/* "352" */ std::string RPL_WHOREPLY(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " " + this->_user + " " + this->_host + " " + this->_server + " " + this->_nickname + " <H|G>[*][@|+] :<hopcount> <real_name>" + "\r\n"); };
			/* "353" */ std::string RPL_NAMREPLY(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "( '=' / '*' / '@' )" + this->_channel + " ' ' : [ '@' / '+' ] " + this->_nickname + " *( ' ' [ '@' / '+' ] " + this->_nickname + " )" + "\r\n"); };
			/* "364" */ std::string RPL_LINKS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<mask> " + this->_server + " :<hopcount> <server_info>" + "\r\n"); };
			/* "365" */ std::string RPL_ENDOFLINKS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<mask> :<info>" + "\r\n"); };
			/* "366" */ std::string RPL_ENDOFNAMES(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<info>" + "\r\n"); };
			/* "367" */ std::string RPL_BANLIST(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " <banid> [<time_left> :<reason>]" + "\r\n"); };
			/* "368" */ std::string RPL_ENDOFBANLIST(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<info>" + "\r\n"); };
			/* "369" */ std::string RPL_ENDOFWHOWAS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + " :<info>" + "\r\n"); };
			/* "371" */ std::string RPL_INFO(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<string>" + "\r\n"); };
			/* "372" */ std::string RPL_MOTD(std::string code, std::string motd) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":- " + motd + "\r\n"); };
			/* "374" */ std::string RPL_ENDOFINFO(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<info>" + "\r\n"); };
			/* "375" */ std::string RPL_MOTDSTART(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":- " + this->_server + " Message of the day -" + "\r\n"); };
			/* "376" */ std::string RPL_ENDOFMOTD(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":End of /MOTD command" + "\r\n"); };
			/* "381" */ std::string RPL_YOUREOPER(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":You are now an IRC operator" + "\r\n"); };
			/* "382" */ std::string RPL_REHASHING(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<config_file> :<info>" + "\r\n"); };
			/* "383" */ std::string RPL_YOURESERVICE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":You are service <service_name>" + "\r\n"); };
			/* "391" */ std::string RPL_TIME(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_server + " :<time string>" + "\r\n"); };
			/* "392" */ std::string RPL_USERSSTART(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":ClientID Terminal Host" + "\r\n"); };
			/* "393" */ std::string RPL_USERS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<username> <ttyline> <hostname>" + "\r\n"); };
			/* "394" */ std::string RPL_ENDOFUSERS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<info>" + "\r\n"); };
			/* "395" */ std::string RPL_NOUSERS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<info>" + "\r\n"); };
			/* "401" */ std::string ERR_NOSUCHNICK(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + " :<reason>" + "\r\n"); };
			/* "402" */ std::string ERR_NOSUCHSERVER(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_server + " :<reason>" + "\r\n"); };
			/* "403" */ std::string ERR_NOSUCHCHANNEL(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "404" */ std::string ERR_CANNOTSENDTOCHAN(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "405" */ std::string ERR_TOOMANYCHANNELS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "406" */ std::string ERR_WASNOSUCHNICK(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + " :<reason>" + "\r\n"); };
			/* "407" */ std::string ERR_TOOMANYTARGETS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<target> :<reason>" + "\r\n"); };
			/* "408" */ std::string ERR_NOSUCHSERVICE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<service_name> :<reason>" + "\r\n"); };
			/* "409" */ std::string ERR_NOORIGIN(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "411" */ std::string ERR_NORECIPIENT(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "412" */ std::string ERR_NOTEXTTOSEND(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "413" */ std::string ERR_NOTOPLEVEL(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<mask> :<reason>" + "\r\n"); };
			/* "414" */ std::string ERR_WILDTOPLEVEL(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<mask> :<reason>" + "\r\n"); };
			/* "415" */ std::string ERR_BADMASK(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<mask> :<reason>" + "\r\n"); };
			/* "416" */ std::string ERR_TOOMANYMATCHES(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<command> [<mask>] :<info>" + "\r\n"); };
			/* "421" */ std::string ERR_UNKNOWNCOMMAND(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<command> :<reason>" + "\r\n"); };
			/* "422" */ std::string ERR_NOMOTD(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "423" */ std::string ERR_NOADMININFO(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_server + " :<reason>" + "\r\n"); };
			/* "424" */ std::string ERR_FILEERROR(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "431" */ std::string ERR_NONICKNAMEGIVEN(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "432" */ std::string ERR_ERRONEUSNICKNAME(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + " :<reason>" + "\r\n"); };
			/* "433" */ std::string ERR_NICKNAMEINUSE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + " :<reason>" + "\r\n"); };
			/* "436" */ std::string ERR_NICKCOLLISION(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + " :<reason>" + "\r\n"); };
			/* "437" */ std::string ERR_UNAVAILRESOURCE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<nick/channel/service> :<reason>" + "\r\n"); };
			/* "441" */ std::string ERR_USERNOTINCHANNEL(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "442" */ std::string ERR_NOTONCHANNEL(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "443" */ std::string ERR_USERONCHANNEL(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_nickname + this->_channel + " [:<reason>]" + "\r\n"); };
			/* "444" */ std::string ERR_NOLOGIN(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_user + " :<reason>" + "\r\n"); };
			/* "445" */ std::string ERR_SUMMONDISABLED(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "446" */ std::string ERR_USERSDISABLED(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "451" */ std::string ERR_NOTREGISTERED(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "461" */ std::string ERR_NEEDMOREPARAMS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<command> :<reason>" + "\r\n"); };
			/* "462" */ std::string ERR_ALREADYREGISTRED(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "463" */ std::string ERR_NOPERMFORHOST(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "464" */ std::string ERR_PASSWDMISMATCH(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":Password incorrect" + "\r\n"); };
			/* "465" */ std::string ERR_YOUREBANNEDCREEP(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "467" */ std::string ERR_KEYSET(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "471" */ std::string ERR_CHANNELISFULL(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "472" */ std::string ERR_UNKNOWNMODE(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<char> :<reason>" + "\r\n"); };
			/* "473" */ std::string ERR_INVITEONLYCHAN(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "474" */ std::string ERR_BANNEDFROMCHAN(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "475" */ std::string ERR_BADCHANNELKEY(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "476" */ std::string ERR_BADCHANMASK(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "477" */ std::string ERR_NOCHANMODES(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "478" */ std::string ERR_BANLISTFULL(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " <char> :<reason>" + "\r\n"); };
			/* "481" */ std::string ERR_NOPRIVILEGES(std::string code, std::string reason) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":" + reason + "\r\n"); };
			/* "482" */ std::string ERR_CHANOPRIVSNEEDED(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "483" */ std::string ERR_CANTKILLSERVER(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "484" */ std::string ERR_RESTRICTED(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "485" */ std::string ERR_UNIQOPRIVSNEEDED(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "491" */ std::string ERR_NOOPERHOST(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "501" */ std::string ERR_UMODEUNKNOWNFLAG(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "502" */ std::string ERR_USERSDONTMATCH(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };

			private :

				std::string	_network;
				std::string	_nickname;
				std::string	_user;
				std::string	_host;
				std::string	_server;
				std::string	_channel;
				std::string	_date_time;
				std::string	_version;
				std::string	_mode;
				std::string	_prefix;
	};

	#endif