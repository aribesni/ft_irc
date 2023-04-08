/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillemette.duchateau <guillemette.duch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:14:00 by guillemette       #+#    #+#             */
/*   Updated: 2023/04/08 12:47:23 by guillemette      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_H
# define REPLIES_H

# include <iostream>
# include "Client.hpp"

	class Replies {

		public :

			Replies(Client & client)
			{
				setVariables(client);
			}
			~Replies(void) {};

			void	setVariables(Client client) {

				this->_network = "Internet Relay";
				this->_nickname = client.getNick();
				this->_user = client.getUser();
				this->_host = client.getHostName() ;
				this->_server = "Ircserv";
				this->_channel = "<channel>";
				this->_date_time = "Tue March 14 at 12:05";
				this->_version = "1.0";
				this->_irc_mode = client.getIRCMode();
				this->_prefix = client.getPrefix();
			}

			void	sendMotd(int client_socket) {

				std::string motd1 = "Welcome to our Ircserv IRC Network !\r\n";
				std::string motd2 = "For any inquiries please refer to aribesni@student.42.fr, gduchate@student.42.fr or rliu@student.42.fr.\r\n";
				std::string motd3 = "Enjoy your time here.\r\n";
				send(client_socket, this->RPL_MOTD("\r\n").data(), this->RPL_MOTD("\r\n").size(), 0);
				send(client_socket, this->RPL_MOTD("\r\n").data(), this->RPL_MOTD("\r\n").size(), 0);
				send(client_socket, this->RPL_MOTD(motd1).data(), this->RPL_MOTD(motd1).size(), 0);
				send(client_socket, this->RPL_MOTD("\r\n").data(), this->RPL_MOTD("\r\n").size(), 0);
				send(client_socket, this->RPL_MOTD(motd2).data(), this->RPL_MOTD(motd2).size(), 0);
				send(client_socket, this->RPL_MOTD("\r\n").data(), this->RPL_MOTD("\r\n").size(), 0);
				send(client_socket, this->RPL_MOTD(motd3).data(), this->RPL_MOTD(motd3).size(), 0);
				send(client_socket, this->RPL_MOTD("\r\n").data(), this->RPL_MOTD("\r\n").size(), 0);
				send(client_socket, this->RPL_MOTD("\r\n").data(), this->RPL_MOTD("\r\n").size(), 0);
			}

			/* "001" */ std::string RPL_WELCOME() { return (":" + this->_prefix + " 001 " + this->_nickname + " " + ":Welcome to the " + this->_network + " Network, " + this->_prefix + "\r\n"); };
			/* "002" */ std::string RPL_YOURHOST() { return (":" + this->_prefix + " 002 " + this->_nickname + " " + ":Your host is " + this->_server + ", running version " + this->_version + "\r\n"); };
			/* "003" */ std::string RPL_CREATED() { return (":" + this->_prefix + " 003 " + this->_nickname + " " + ":This server was created " + this->_date_time + "\r\n"); };
			/* "004" */ std::string RPL_MYINFO() { return (":" + this->_prefix + " 004 " + this->_nickname + " " + this->_server + " " + this->_version + " <user_modes> <chan_modes>" + "\r\n"); };
			/* "005" */ std::string RPL_BOUNCE() { return (":" + this->_prefix + " 005 " + this->_nickname + " " + this->_server + " " + this->_version + " <user_modes> <chan_modes> <channel_modes_with_params> <user_modes_with_params> <server_modes> <server_modes_with_params>" + "\r\n"); };
			/* "043" */ std::string RPL_SAVENICK() { return (":" + this->_prefix + " 043 " + this->_nickname + " " + ":<info>" + "\r\n"); };
			/* "200" */ std::string RPL_TRACELINK() { return (":" + this->_prefix + " 200 " + this->_nickname + " " + "Link " + this->_version + "[.<debug_level>] <destination> <next_server> [V<protocol_version> <link_uptime_in_seconds> <backstream_sendq> <upstream_sendq>]" + "\r\n"); };
			/* "201" */ std::string RPL_TRACECONNECTING() { return (":" + this->_prefix + " 201 " + this->_nickname + " " + "Try. <class> " + this->_server + "\r\n"); };
			/* "202" */ std::string RPL_TRACEHANDSHAKE() { return (":" + this->_prefix + " 202 " + this->_nickname + " " + "H.S. <class> " + this->_server + "\r\n"); };
			/* "203" */ std::string RPL_TRACEUNKNOWN() { return (":" + this->_prefix + " 203 " + this->_nickname + " " + "???? <class> [<connection_address>]" + "\r\n"); };
			/* "204" */ std::string RPL_TRACEOPERATOR() { return (":" + this->_prefix + " 204 " + this->_nickname + " " + "Oper <class> " + this->_nickname + "\r\n"); };
			/* "205" */ std::string RPL_TRACEUSER() { return (":" + this->_prefix + " 205 " + this->_nickname + " " + "Client <class> " + this->_nickname + "\r\n"); };
			/* "206" */ std::string RPL_TRACESERVER() { return (":" + this->_prefix + " 206 " + this->_nickname + " " + "Serv <class> <int>S <int>C " + this->_server + " <nick!user|*!*>@<host|server> [V<protocol_version>]" + "\r\n"); };
			/* "207" */ std::string RPL_TRACESERVICE() { return (":" + this->_prefix + " 207 " + this->_nickname + " " + "Service <class> <name> <type> <active_type>" + "\r\n"); };
			/* "208" */ std::string RPL_TRACENEWTYPE() { return (":" + this->_prefix + " 208 " + this->_nickname + " " + "<newtype> 0 <client_name>" + "\r\n"); };
			/* "209" */ std::string RPL_TRACECLASS() { return (":" + this->_prefix + " 209 " + this->_nickname + " " + "Class <class> <count>" + "\r\n"); };
			/* "211" */ std::string RPL_STATSLINKINFO() { return (":" + this->_prefix + " 211 " + this->_nickname + " " + "<linkname> <sendq> <sent_msgs> <sent_bytes> <recvd_msgs> <rcvd_bytes> <time_open>" + "\r\n"); };
			/* "212" */ std::string RPL_STATSCOMMANDS() { return (":" + this->_prefix + " 212 " + this->_nickname + " " + "<command> <count> [<byte_count> <remote_count>]" + "\r\n"); };
			/* "213" */ std::string RPL_STATSCLINE() { return (":" + this->_prefix + " 213 " + this->_nickname + " " + "C " + this->_host + " * <name> <port> <class>" + "\r\n"); };
			/* "214" */ std::string RPL_STATSNLINE() { return (":" + this->_prefix + " 214 " + this->_nickname + " " + "N " + this->_host + " * <name> <port> <class>" + "\r\n"); };
			/* "215" */ std::string RPL_STATSILINE() { return (":" + this->_prefix + " 215 " + this->_nickname + " " + "I " + this->_host + " * " + this->_host + " <port> <class>" + "\r\n"); };
			/* "216" */ std::string RPL_STATSKLINE() { return (":" + this->_prefix + " 216 " + this->_nickname + " " + "K " + this->_host + " * <username> <port> <class>" + "\r\n"); };
			/* "218" */ std::string RPL_STATSYLINE() { return (":" + this->_prefix + " 218 " + this->_nickname + " " + "Y <class> <ping_freq> <connect_freq> <max_sendq>" + "\r\n"); };
			/* "219" */ std::string RPL_ENDOFSTATS() { return (":" + this->_prefix + " 219 " + this->_nickname + " " + "<query> :<info>" + "\r\n"); };
			/* "221" */ std::string RPL_UMODEIS() { return (":" + this->_prefix + " 221 " + this->_nickname + " " + "+" + this->_irc_mode + "\r\n"); };
			/* "234" */ std::string RPL_SERVLIST() { return (":" + this->_prefix + " 234 " + this->_nickname + " " + "<name> " + this->_server + " <mask> <type> <hopcount> <info>" + "\r\n"); };
			/* "235" */ std::string RPL_SERVLISTEND() { return (":" + this->_prefix + " 235 " + this->_nickname + " " + "<mask> <type> :<info>" + "\r\n"); };
			/* "241" */ std::string RPL_STATSLLINE() { return (":" + this->_prefix + " 241 " + this->_nickname + " " + "L <hostmask> * " + this->_server + " <maxdepth>" + "\r\n"); };
			/* "242" */ std::string RPL_STATSUPTIME() { return (":" + this->_prefix + " 242 " + this->_nickname + " " + ":Server Up <days> days <hours>:<minutes>:<seconds>" + "\r\n"); };
			/* "243" */ std::string RPL_STATSOLINE() { return (":" + this->_prefix + " 243 " + this->_nickname + " " + "O <hostmask> * " + this->_nickname + " [:<info>]" + "\r\n"); };
			/* "244" */ std::string RPL_STATSHLINE() { return (":" + this->_prefix + " 244 " + this->_nickname + " " + "H <hostmask> * " + this->_server + "\r\n"); };
			/* "251" */ std::string RPL_LUSERCLIENT() { return (":" + this->_prefix + " 251 " + this->_nickname + " " + ":There are <int> users and <int> invisible on <int> servers" + "\r\n"); };
			/* "252" */ std::string RPL_LUSEROP() { return (":" + this->_prefix + " 252 " + this->_nickname + " " + "<int> :<info>" + "\r\n"); };
			/* "253" */ std::string RPL_LUSERUNKNOWN() { return (":" + this->_prefix + " 253 " + this->_nickname + " " + "<int> :<info>" + "\r\n"); };
			/* "254" */ std::string RPL_LUSERCHANNELS() { return (":" + this->_prefix + " 254 " + this->_nickname + " " + "<int> :<info>" + "\r\n"); };
			/* "255" */ std::string RPL_LUSERME() { return (":" + this->_prefix + " 255 " + this->_nickname + " " + ":I have <int> clients and <int> servers" + "\r\n"); };
			/* "256" */ std::string RPL_ADMINME() { return (":" + this->_prefix + " 256 " + this->_nickname + " " + this->_server + " :<info>" + "\r\n"); };
			/* "257" */ std::string RPL_ADMINLOC1() { return (":" + this->_prefix + " 257 " + this->_nickname + " " + ":<admin_location>" + "\r\n"); };
			/* "258" */ std::string RPL_ADMINLOC2() { return (":" + this->_prefix + " 258 " + this->_nickname + " " + ":<admin_location>" + "\r\n"); };
			/* "259" */ std::string RPL_ADMINEMAIL() { return (":" + this->_prefix + " 259 " + this->_nickname + " " + ":<email_address>" + "\r\n"); };
			/* "261" */ std::string RPL_TRACELOG() { return (":" + this->_prefix + " 261 " + this->_nickname + " " + "File <logfile> <debug_level>" + "\r\n"); };
			/* "262" */ std::string RPL_TRACEEND() { return (":" + this->_prefix + " 262 " + this->_nickname + " " + this->_server + " " + this->_version + "[.<debug_level>] :<info>" + "\r\n"); };
			/* "263" */ std::string RPL_TRYAGAIN() { return (":" + this->_prefix + " 263 " + this->_nickname + " " + "<command> :<info>" + "\r\n"); };
			/* "301" */ std::string RPL_AWAY() { return (":" + this->_prefix + " 301 " + this->_nickname + " " + this->_nickname + " :<message>" + "\r\n"); };
			/* "302" */ std::string RPL_USERHOST() { return (":" + this->_prefix + " 302 " + this->_nickname + " " + ":*1<reply> *( ' ' <reply> )" + "\r\n"); };
			/* "303" */ std::string RPL_ISON() { return (":" + this->_prefix + " 303 " + this->_nickname + " " + ":*1" + this->_nickname + " *( ' ' " + this->_nickname + " )" + "\r\n"); };
			/* "305" */ std::string RPL_UNAWAY() { return (":" + this->_prefix + " 305 " + this->_nickname + " " + ":<info>" + "\r\n"); };
			/* "306" */ std::string RPL_NOWAWAY() { return (":" + this->_prefix + " 306 " + this->_nickname + " " + ":<info>" + "\r\n"); };
			/* "311" */ std::string RPL_WHOISUSER() { return (":" + this->_prefix + " 311 " + this->_nickname + " " + this->_nickname + this->_user + " " + this->_host + " * :<real_name>" + "\r\n"); };
			/* "312" */ std::string RPL_WHOISSERVER() { return (":" + this->_prefix + " 312 " + this->_nickname + " " + this->_nickname +  " " + this->_server + " :<server_info>" + "\r\n"); };
			/* "313" */ std::string RPL_WHOISOPERATOR() { return (":" + this->_prefix + " 313 " + this->_nickname + " " + this->_nickname + " :<privileges>" + "\r\n"); };
			/* "314" */ std::string RPL_WHOWASUSER() { return (":" + this->_prefix + " 314 " + this->_nickname + " " + this->_nickname + this->_user + " " + this->_host + " * :<real_name>" + "\r\n"); };
			/* "315" */ std::string RPL_ENDOFWHO() { return (":" + this->_prefix + " 315 " + this->_nickname + " " + "<name> :<info>" + "\r\n"); };
			/* "317" */ std::string RPL_WHOISIDLE() { return (":" + this->_prefix + " 317 " + this->_nickname + " " + this->_nickname + " <seconds> :seconds idle" + "\r\n"); };
			/* "318" */ std::string RPL_ENDOFWHOIS() { return (":" + this->_prefix + " 318 " + this->_nickname + " " + this->_nickname + " :<info>" + "\r\n"); };
			/* "319" */ std::string RPL_WHOISCHANNELS() { return (":" + this->_prefix + " 319 " + this->_nickname + " " + this->_nickname + " :*( ( '@' / '+' ) " + this->_channel + " ' ' )" + "\r\n"); };
			/* "321" */ std::string RPL_LISTSTART() { return (":" + this->_prefix + " 321 " + this->_nickname + " " + "Channels :Clients Name" + "\r\n"); };
			/* "322" */ std::string RPL_LIST() { return (":" + this->_prefix + " 322 " + this->_nickname + " " + this->_channel + " <#_visible> :<topic>" + "\r\n"); };
			/* "323" */ std::string RPL_LISTEND() { return (":" + this->_prefix + " 323 " + this->_nickname + " " + ":<info>" + "\r\n"); };
			/* "324" */ std::string RPL_CHANNELMODEIS() { return (":" + this->_prefix + " 324 " + this->_nickname + " " + this->_channel + " <mode> <mode_params>" + "\r\n"); };
			/* "325" */ std::string RPL_UNIQOPIS() { return (":" + this->_prefix + " 325 " + this->_nickname + " " + this->_channel + " <nickname>" + "\r\n"); };
			/* "331" */ std::string RPL_NOTOPIC() { return (":" + this->_prefix + " 331 " + this->_nickname + " " + this->_channel + " :<info>" + "\r\n"); };
			/* "332" */ std::string RPL_TOPIC() { return (":" + this->_prefix + " 332 " + this->_nickname + " " + this->_channel + " :<topic>" + "\r\n"); };
			/* "341" */ std::string RPL_INVITING(std::string target, std::string channel) { return (":" + this->_prefix + " 341 " + this->_nickname + " " + target + " " + channel + "\r\n"); };
			/* "342" */ std::string RPL_SUMMONING() { return (":" + this->_prefix + " 342 " + this->_nickname + " " + this->_user + " :<info>" + "\r\n"); };
			/* "345" */ std::string RPL_ENDOFREOPLIST() { return (":" + this->_prefix + " 345 " + this->_nickname + " " + this->_channel + " <user being invited> <user issuing invite> :<user being invited> has been invited by <user issuing invite>" + "\r\n"); };
			/* "346" */ std::string RPL_INVITELIST() { return (":" + this->_prefix + " 346 " + this->_nickname + " " + this->_channel + " <invitemask>" + "\r\n"); };
			/* "347" */ std::string RPL_ENDOFINVITELIST() { return (":" + this->_prefix + " 347 " + this->_nickname + " " + this->_channel + " :<info>" + "\r\n"); };
			/* "348" */ std::string RPL_EXCEPTLIST() { return (":" + this->_prefix + " 348 " + this->_nickname + " " + this->_channel + " <exceptionmask>" + "\r\n"); };
			/* "349" */ std::string RPL_ENDOFEXCEPTLIST() { return (":" + this->_prefix + " 349 " + this->_nickname + " " + this->_channel + " :<info>" + "\r\n"); };
			/* "351" */ std::string RPL_VERSION() { return (":" + this->_prefix + " 351 " + this->_nickname + " " + this->_version + "[.<debuglevel>] " + this->_server + " :<comments>" + "\r\n"); };
			/* "352" */ std::string RPL_WHOREPLY() { return (":" + this->_prefix + " 352 " + this->_nickname + " " + this->_channel + " " + this->_user + " " + this->_host + " " + this->_server + " " + this->_nickname + " <H|G>[*][@|+] :<hopcount> <real_name>" + "\r\n"); };
			/* "353" */ std::string RPL_NAMREPLY(std::string channel, std::string arg1, std::string arg2) { return (":" + this->_prefix + " 353 " + this->_nickname + " " + arg1 + " " + channel + " :" + arg2 + this->_nickname + /*" *( ' ' [ " + arg3 + " ] " + this->_nickname + " )" + */"\r\n"); };
			/* "364" */ std::string RPL_LINKS() { return (":" + this->_prefix + " 364 " + this->_nickname + " " + "<mask> " + this->_server + " :<hopcount> <server_info>" + "\r\n"); };
			/* "365" */ std::string RPL_ENDOFLINKS() { return (":" + this->_prefix + " 365 " + this->_nickname + " " + "<mask> :<info>" + "\r\n"); };
			/* "366" */ std::string RPL_ENDOFNAMES(std::string channel) { return (":" + this->_prefix + " 366 " + this->_nickname + " " + channel + " :End of /NAMES list" + "\r\n"); };
			/* "367" */ std::string RPL_BANLIST() { return (":" + this->_prefix + " 367 " + this->_nickname + " " + this->_channel + " <banid> [<time_left> :<reason>]" + "\r\n"); };
			/* "368" */ std::string RPL_ENDOFBANLIST() { return (":" + this->_prefix + " 368 " + this->_nickname + " " + this->_channel + " :<info>" + "\r\n"); };
			/* "369" */ std::string RPL_ENDOFWHOWAS() { return (":" + this->_prefix + " 369 " + this->_nickname + " " + this->_nickname + " :<info>" + "\r\n"); };
			/* "371" */ std::string RPL_INFO() { return (":" + this->_prefix + " 371 " + this->_nickname + " " + ":<string>" + "\r\n"); };
			/* "372" */ std::string RPL_MOTD(std::string motd) { return (":" + this->_prefix + " 372 " + this->_nickname + " " + ":- " + motd + "\r\n"); };
			/* "374" */ std::string RPL_ENDOFINFO() { return (":" + this->_prefix + " 374 " + this->_nickname + " " + ":<info>" + "\r\n"); };
			/* "375" */ std::string RPL_MOTDSTART() { return (":" + this->_prefix + " 375 " + this->_nickname + " " + ":- " + this->_server + " Message of the day -" + "\r\n"); };
			/* "376" */ std::string RPL_ENDOFMOTD() { return (":" + this->_prefix + " 376 " + this->_nickname + " " + ":End of /MOTD command" + "\r\n"); };
			/* "381" */ std::string RPL_YOUREOPER() { return (":" + this->_prefix + " 381 " + this->_nickname + " " + ":You are now an IRC operator" + "\r\n"); };
			/* "382" */ std::string RPL_REHASHING() { return (":" + this->_prefix + " 382 " + this->_nickname + " " + "<config_file> :<info>" + "\r\n"); };
			/* "383" */ std::string RPL_YOURESERVICE() { return (":" + this->_prefix + " 383 " + this->_nickname + " " + ":You are service <service_name>" + "\r\n"); };
			/* "391" */ std::string RPL_TIME() { return (":" + this->_prefix + " 391 " + this->_nickname + " " + this->_server + " :<time string>" + "\r\n"); };
			/* "392" */ std::string RPL_USERSSTART() { return (":" + this->_prefix + " 392 " + this->_nickname + " " + ":ClientID Terminal Host" + "\r\n"); };
			/* "393" */ std::string RPL_USERS() { return (":" + this->_prefix + " 393 " + this->_nickname + " " + ":<username> <ttyline> <hostname>" + "\r\n"); };
			/* "394" */ std::string RPL_ENDOFUSERS() { return (":" + this->_prefix + " 394 " + this->_nickname + " " + ":<info>" + "\r\n"); };
			/* "395" */ std::string RPL_NOUSERS() { return (":" + this->_prefix + " 395 " + this->_nickname + " " + ":<info>" + "\r\n"); };
			/* "401" */ std::string ERR_NOSUCHNICK(std::string nickname) { return (":" + this->_prefix + " 401 " + this->_nickname + " " + nickname + " No such nick/channel" + "\r\n"); };
			/* "402" */ std::string ERR_NOSUCHSERVER() { return (":" + this->_prefix + " 402 " + this->_nickname + " " + this->_server + " :<reason>" + "\r\n"); };
			/* "403" */ std::string ERR_NOSUCHCHANNEL(std::string channel) { return (":" + this->_prefix + " 403 " + this->_nickname + " " + channel + " :No such channel" + "\r\n"); };
			/* "404" */ std::string ERR_CANNOTSENDTOCHAN() { return (":" + this->_prefix + " 404 " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "405" */ std::string ERR_TOOMANYCHANNELS() { return (":" + this->_prefix + " 405 " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "406" */ std::string ERR_WASNOSUCHNICK() { return (":" + this->_prefix + " 406 " + this->_nickname + " " + this->_nickname + " :<reason>" + "\r\n"); };
			/* "407" */ std::string ERR_TOOMANYTARGETS() { return (":" + this->_prefix + " 407 " + this->_nickname + " " + "<target> :<reason>" + "\r\n"); };
			/* "408" */ std::string ERR_NOSUCHSERVICE() { return (":" + this->_prefix + " 408 " + this->_nickname + " " + "<service_name> :<reason>" + "\r\n"); };
			/* "409" */ std::string ERR_NOORIGIN() { return (":" + this->_prefix + " 409 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "411" */ std::string ERR_NORECIPIENT(std::string cmd) { return (":" + this->_prefix + " 411 " + this->_nickname + ":No recipient given (" + cmd + ")" + "\r\n"); };
			/* "412" */ std::string ERR_NOTEXTTOSEND() { return (":" + this->_prefix + " 412 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "413" */ std::string ERR_NOTOPLEVEL() { return (":" + this->_prefix + " 413 " + this->_nickname + " " + "<mask> :<reason>" + "\r\n"); };
			/* "414" */ std::string ERR_WILDTOPLEVEL() { return (":" + this->_prefix + " 414 " + this->_nickname + " " + "<mask> :<reason>" + "\r\n"); };
			/* "415" */ std::string ERR_BADMASK() { return (":" + this->_prefix + " 415 " + this->_nickname + " " + "<mask> :<reason>" + "\r\n"); };
			/* "416" */ std::string ERR_TOOMANYMATCHES() { return (":" + this->_prefix + " 416 " + this->_nickname + " " + "<command> [<mask>] :<info>" + "\r\n"); };
			/* "421" */ std::string ERR_UNKNOWNCOMMAND() { return (":" + this->_prefix + " 421 " + this->_nickname + " " + "<command> :<reason>" + "\r\n"); };
			/* "422" */ std::string ERR_NOMOTD() { return (":" + this->_prefix + " 422 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "423" */ std::string ERR_NOADMININFO() { return (":" + this->_prefix + " 423 " + this->_nickname + " " + this->_server + " :<reason>" + "\r\n"); };
			/* "424" */ std::string ERR_FILEERROR() { return (":" + this->_prefix + " 424 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "431" */ std::string ERR_NONICKNAMEGIVEN() { return (":" + this->_prefix + " 431 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "432" */ std::string ERR_ERRONEUSNICKNAME() { return (":" + this->_prefix + " 432 " + this->_nickname + " " + this->_nickname + " :<reason>" + "\r\n"); };
			/* "433" */ std::string ERR_NICKNAMEINUSE() { return (":" + this->_prefix + " 433 " + this->_nickname + " " + this->_nickname + " :<reason>" + "\r\n"); };
			/* "436" */ std::string ERR_NICKCOLLISION() { return (":" + this->_prefix + " 436 " + this->_nickname + " " + this->_nickname + " :<reason>" + "\r\n"); };
			/* "437" */ std::string ERR_UNAVAILRESOURCE() { return (":" + this->_prefix + " 437 " + this->_nickname + " " + "<nick/channel/service> :<reason>" + "\r\n"); };
			/* "441" */ std::string ERR_USERNOTINCHANNEL(std::string channel) { return (":" + this->_prefix + " 441 " + this->_nickname + " " + this->_nickname + " " + channel + " :They are not on that channel" + "\r\n"); };
			/* "442" */ std::string ERR_NOTONCHANNEL(std::string channel) { return (":" + this->_prefix + " 442 " + this->_nickname + " " + channel + " :You're not on that channel" + "\r\n"); };
			/* "443" */ std::string ERR_USERONCHANNEL() { return (":" + this->_prefix + " 443 " + this->_nickname + " " + this->_nickname + this->_channel + " [:<reason>]" + "\r\n"); };
			/* "444" */ std::string ERR_NOLOGIN() { return (":" + this->_prefix + " 444 " + this->_nickname + " " + this->_user + " :<reason>" + "\r\n"); };
			/* "445" */ std::string ERR_SUMMONDISABLED() { return (":" + this->_prefix + " 445 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "446" */ std::string ERR_USERSDISABLED() { return (":" + this->_prefix + " 446 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "451" */ std::string ERR_NOTREGISTERED() { return (":" + this->_prefix + " 451 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "461" */ std::string ERR_NEEDMOREPARAMS(std::string command) { return (":" + this->_prefix + " 461 " + this->_nickname + " " + command + " :Not enough parameters" + "\r\n"); };
			/* "462" */ std::string ERR_ALREADYREGISTRED() { return (":" + this->_prefix + " 462 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "463" */ std::string ERR_NOPERMFORHOST() { return (":" + this->_prefix + " 463 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "464" */ std::string ERR_PASSWDMISMATCH() { return (":" + this->_prefix + " 464 " + this->_nickname + " " + ":Password incorrect" + "\r\n"); };
			/* "465" */ std::string ERR_YOUREBANNEDCREEP() { return (":" + this->_prefix + " 465 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "467" */ std::string ERR_KEYSET() { return (":" + this->_prefix + " 467 " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "471" */ std::string ERR_CHANNELISFULL() { return (":" + this->_prefix + " 471 " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "472" */ std::string ERR_UNKNOWNMODE() { return (":" + this->_prefix + " 472 " + this->_nickname + " " + "<char> :<reason>" + "\r\n"); };
			/* "473" */ std::string ERR_INVITEONLYCHAN() { return (":" + this->_prefix + " 473 " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "474" */ std::string ERR_BANNEDFROMCHAN() { return (":" + this->_prefix + " 474 " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "475" */ std::string ERR_BADCHANNELKEY() { return (":" + this->_prefix + " 475 " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "476" */ std::string ERR_BADCHANMASK() { return (":" + this->_prefix + " 476 " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "477" */ std::string ERR_NOCHANMODES() { return (":" + this->_prefix + " 477 " + this->_nickname + " " + this->_channel + " :<reason>" + "\r\n"); };
			/* "478" */ std::string ERR_BANLISTFULL() { return (":" + this->_prefix + " 478 " + this->_nickname + " " + this->_channel + " <char> :<reason>" + "\r\n"); };
			/* "481" */ std::string ERR_NOPRIVILEGES(std::string reason) { return (":" + this->_prefix + " 481 " + this->_nickname + " " + ":" + reason + "\r\n"); };
			/* "482" */ std::string ERR_CHANOPRIVSNEEDED(std::string channel) { return (":" + this->_prefix + " 482 " + this->_nickname + " " + channel + " :You're not channel operator" + "\r\n"); };
			/* "483" */ std::string ERR_CANTKILLSERVER() { return (":" + this->_prefix + " 483 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "484" */ std::string ERR_RESTRICTED() { return (":" + this->_prefix + " 484 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "485" */ std::string ERR_UNIQOPRIVSNEEDED() { return (":" + this->_prefix + " 485 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "491" */ std::string ERR_NOOPERHOST() { return (":" + this->_prefix + " 491 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "501" */ std::string ERR_UMODEUNKNOWNFLAG() { return (":" + this->_prefix + " 501 " + this->_nickname + " " + ":<reason>" + "\r\n"); };
			/* "502" */ std::string ERR_USERSDONTMATCH() { return (":" + this->_prefix + " 502 " + this->_nickname + " " + ":<reason>" + "\r\n"); };

			private :

				std::string	_network;
				std::string	_nickname;
				std::string	_user;
				std::string	_host;
				std::string	_server;
				std::string	_channel;
				std::string	_date_time;
				std::string	_version;
				std::string	_irc_mode;
				std::string	_prefix;
	};

	#endif