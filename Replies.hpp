/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:14:00 by guillemette       #+#    #+#             */
/*   Updated: 2023/03/24 18:31:56 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_H
# define REPLIES_H

# include <iostream>
# include "Client.hpp"

	class Replies {

		public :

			Replies(Client &client)
			{
				this->_network = "Internet Relay Network";
				this->_nickname = client.getNick();
				this->_user = client.getUser();
				this->_host = "localhost";
				this->_server = "Ircserv";
				this->_channel = "<channel>";
				this->_date_time = "Tue March 14 at 12:05";
				this->_version = "1.0";
				this->_prefix = client.getPrefix();
			}
			~Replies(void) {};
			std::map<std::string, std::string>	_replies;//add_ran
						std::map<std::string, std::string> getReplies(std::string nick, std::string user, std::string prefix){
				this->_nickname = nick;
				this->_user = user;
				this->_prefix = prefix;
				init_replies();
				return (_replies);
			}			
			void init_replies(void){
			_replies["001"] = RPL_WELCOME("001");
			_replies["002"] = RPL_YOURHOST("002");
			_replies["003"] = RPL_CREATED("003");
			_replies["004"] = RPL_MYINFO("004");
			_replies["005"] = RPL_BOUNCE("005");
			_replies["043"] = RPL_SAVENICK("043");
			_replies["202"] = RPL_TRACEHANDSHAKE("202");
			_replies["203"] = RPL_TRACEUNKNOWN("203");
			_replies["204"] = RPL_TRACEOPERATOR("204");
			_replies["205"] = RPL_TRACEUSER("205"); 
			_replies["206"] = RPL_TRACESERVER("206"); 
			_replies["207"] = RPL_TRACESERVICE("207");
			_replies["208"] = RPL_TRACENEWTYPE("208"); 
			_replies["209"] = RPL_TRACECLASS("209"); 
			_replies["211"] = RPL_STATSLINKINFO("211"); 
			_replies["213"] = RPL_STATSCLINE("213"); 
			_replies["214"] = RPL_STATSNLINE("214"); 
			_replies["215"] = RPL_STATSILINE("215"); 
			_replies["216"] = RPL_STATSKLINE("216");
			_replies["218"] = RPL_STATSYLINE("218");
			_replies["219"] = RPL_ENDOFSTATS("219"); 
			_replies["221"] = RPL_UMODEIS("221"); 
			_replies["234"] = RPL_SERVLIST("234");
			_replies["235"] = RPL_SERVLISTEND("235"); 
			_replies["241"] = RPL_STATSLLINE("241");
			_replies["242"] = RPL_STATSUPTIME("242"); 
			_replies["243"] = RPL_STATSOLINE("243"); 
			_replies["244"] = RPL_STATSHLINE("244"); 
			_replies["251"] = RPL_LUSERCLIENT("251"); 
			_replies["252"] = RPL_LUSEROP("252"); 
			_replies["253"] = RPL_LUSERUNKNOWN("253"); 
			_replies["254"] = RPL_LUSERCHANNELS("254"); 
			_replies["255"] = RPL_LUSERME("255"); 
			_replies["256"] = RPL_ADMINME("256"); 
			_replies["257"] = RPL_ADMINLOC1("257"); 
			_replies["258"] = RPL_ADMINLOC2("258");
			_replies["259"] = RPL_ADMINEMAIL("259"); 
			_replies["261"] = RPL_TRACELOG("261");
			_replies["262"] = RPL_TRACEEND("262"); 
			_replies["263"] = RPL_TRYAGAIN("263");
			_replies["301"] = RPL_AWAY("301");
			_replies["302"] = RPL_USERHOST("302"); 
			_replies["303"] = RPL_ISON("303"); 
			_replies["305"] = RPL_UNAWAY("305"); 
			_replies["306"] = RPL_NOWAWAY("306");
			_replies["311"] = RPL_WHOISUSER("311"); 
			_replies["312"] = RPL_WHOISSERVER("312");
			_replies["313"] = RPL_WHOISOPERATOR("313");
			_replies["314"] = RPL_WHOWASUSER("314");
			_replies["315"] = RPL_ENDOFWHO("315"); 
			_replies["317"] = RPL_WHOISIDLE("317");
			_replies["318"] = RPL_ENDOFWHOIS("318");
			_replies["319"] = RPL_WHOISCHANNELS("319"); 
			_replies["321"] = RPL_LISTSTART("321"); 
			_replies["322"] = RPL_LIST("322"); 
			_replies["323"] = RPL_LISTEND("323"); 
			_replies["324"] = RPL_CHANNELMODEIS("324"); 
			_replies["325"] = RPL_UNIQOPIS("325");
			_replies["331"] = RPL_NOTOPIC("331");
			_replies["332"] = RPL_TOPIC("332"); 
			_replies["341"] = RPL_INVITING("341");  
			_replies["342"] = RPL_SUMMONING("342"); 
			_replies["345"] = RPL_ENDOFREOPLIST("345");
			_replies["347"] = RPL_ENDOFINVITELIST("347");
			_replies["348"] = RPL_EXCEPTLIST("348");
			_replies["349"] = RPL_ENDOFEXCEPTLIST("349");
			_replies["351"] = RPL_VERSION("351"); 
			_replies["352"] = RPL_WHOREPLY("352");
			_replies["353"] = RPL_NAMREPLY("353");  
			_replies["364"] = RPL_LINKS("364");
			_replies["365"] = RPL_ENDOFLINKS("365"); 
			_replies["366"] = RPL_ENDOFNAMES("366");
			_replies["367"] = RPL_BANLIST("367"); 
			_replies["368"] = RPL_ENDOFBANLIST("368");
			_replies["369"] = RPL_ENDOFWHOWAS("369");
			//_replies["372"] = RPL_MOTD("372");
			_replies["375"] = RPL_MOTDSTART("375");
			_replies["376"] = RPL_ENDOFMOTD("376"); 
			_replies["381"] = RPL_YOUREOPER("381"); 
			_replies["382"] = RPL_REHASHING("382"); 
			_replies["383"] = RPL_YOURESERVICE("383"); 
			_replies["391"] = RPL_TIME("391"); 
			_replies["392"] = RPL_USERSSTART("392"); 
			_replies["393"] = RPL_USERS("393");
			_replies["394"] = RPL_ENDOFUSERS("394"); 
			_replies["395"] = RPL_NOUSERS("395"); 
			_replies["401"] = ERR_NOSUCHNICK("401");
			_replies["402"] = ERR_NOSUCHSERVER("402");
			_replies["403"] = ERR_NOSUCHCHANNEL("403");
			_replies["404"] = ERR_CANNOTSENDTOCHAN("404");
			_replies["405"] = ERR_TOOMANYCHANNELS("405"); 
			_replies["406"] = ERR_WASNOSUCHNICK("406");
			_replies["407"] = ERR_TOOMANYTARGETS("407"); 
			_replies["411"] = ERR_NORECIPIENT("411"); 
			_replies["412"] = ERR_NOTEXTTOSEND("412");
			_replies["413"] = ERR_NOTOPLEVEL("413");
			_replies["414"] = ERR_WILDTOPLEVEL("414");
			_replies["415"] = ERR_BADMASK("415"); 
			_replies["416"] = ERR_TOOMANYMATCHES("416");
			_replies["421"] = ERR_UNKNOWNCOMMAND("421");  
			_replies["422"] = ERR_NOMOTD("422"); 
			_replies["423"] = ERR_NOADMININFO("423");
			_replies["424"] = ERR_FILEERROR("424"); 
			_replies["431"] = ERR_NONICKNAMEGIVEN("431"); 
			_replies["432"] = ERR_ERRONEUSNICKNAME("432");
			_replies["433"] = ERR_NICKNAMEINUSE("433"); 
			_replies["436"] = ERR_NICKCOLLISION("436"); 
			_replies["437"] = ERR_UNAVAILRESOURCE("437");
			_replies["441"] = ERR_USERNOTINCHANNEL("441");
			_replies["442"] = ERR_NOTONCHANNEL("442");
			_replies["443"] = ERR_USERONCHANNEL("443");
			_replies["444"] = ERR_NOLOGIN("444"); 
			_replies["445"] = ERR_SUMMONDISABLED("445");
			_replies["446"] = ERR_USERSDISABLED("446"); 
			_replies["451"] = ERR_NOTREGISTERED("451"); 
			_replies["461"] = ERR_NEEDMOREPARAMS("461");
			_replies["462"] = ERR_ALREADYREGISTRED("462");
			_replies["463"] = ERR_NOPERMFORHOST("463"); 
			_replies["464"] = ERR_PASSWDMISMATCH("464");
			_replies["465"] = ERR_YOUREBANNEDCREEP("465");
			_replies["467"] = ERR_KEYSET("467");
			_replies["471"] = ERR_CHANNELISFULL("471");
			_replies["472"] = ERR_UNKNOWNMODE("472");
			_replies["473"] = ERR_INVITEONLYCHAN("473");
			_replies["474"] = ERR_BANNEDFROMCHAN("474");
			_replies["475"] = ERR_BADCHANNELKEY("475");
			_replies["476"] = ERR_BADCHANMASK("476");
			_replies["477"] = ERR_NOCHANMODES("477");
			_replies["478"] = ERR_BANLISTFULL("478");
			_replies["481"] = ERR_NOPRIVILEGES("481"); 
			_replies["482"] = ERR_CHANOPRIVSNEEDED("482");
			_replies["483"] = ERR_CANTKILLSERVER("483"); 
			_replies["484"] = ERR_RESTRICTED("484"); 
			_replies["485"] = ERR_UNIQOPRIVSNEEDED("485");
			_replies["491"] = ERR_NOOPERHOST("491"); 
			_replies["501"] = ERR_UMODEUNKNOWNFLAG("501");
			_replies["502"] = ERR_USERSDONTMATCH("502");
			}
			void	sendMotd(int client_socket) {

				std::string motd1 = "Welcome to our Ircserv IRC Network !\n";
				std::string motd2 = "For any inquiries please refer to aribesni@student.42.fr, gduchate@student.42.fr or rliu@student.42.fr.\n";
				std::string motd3 = "Enjoy your time here.\n";
				send(client_socket, this->RPL_MOTD("372", "\n").data(), this->RPL_MOTD("372", "\n").size(), 0);
				send(client_socket, this->RPL_MOTD("372", "\n").data(), this->RPL_MOTD("372", "\n").size(), 0);
				send(client_socket, this->RPL_MOTD("372", motd1).data(), this->RPL_MOTD("372", motd1).size(), 0);
				send(client_socket, this->RPL_MOTD("372", "\n").data(), this->RPL_MOTD("372", "\n").size(), 0);
				send(client_socket, this->RPL_MOTD("372", motd2).data(), this->RPL_MOTD("372", motd2).size(), 0);
				send(client_socket, this->RPL_MOTD("372", "\n").data(), this->RPL_MOTD("372", "\n").size(), 0);
				send(client_socket, this->RPL_MOTD("372", motd3).data(), this->RPL_MOTD("372", motd3).size(), 0);
				send(client_socket, this->RPL_MOTD("372", "\n").data(), this->RPL_MOTD("372", "\n").size(), 0);
				send(client_socket, this->RPL_MOTD("372", "\n").data(), this->RPL_MOTD("372", "\n").size(), 0);
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
			/* "221" */ std::string RPL_UMODEIS(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + "<user_modes> [<user_mode_params>]" + "\r\n"); };
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
			/* "381" */ std::string RPL_YOUREOPER(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<info>" + "\r\n"); };
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
			/* "411" */ std::string ERR_NORECIPIENT(std::string cmd) { return (":" + this->_prefix + " 411 " + this->_nickname + ":No recipient given (" + cmd + ")" + "\r\n"); };
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
			/* "464" */ std::string ERR_PASSWDMISMATCH(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
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
			/* "481" */ std::string ERR_NOPRIVILEGES(std::string code) { return (":" + this->_prefix + " " + code + " " + this->_nickname + " " + ":<reason>" + "\r\n"); };
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
				std::string	_prefix;
	};

	#endif