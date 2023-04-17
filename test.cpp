numericReply(srv, fd, "311", RPL_WHOISUSER(nickname, username, hostname, realname)));

std::string	numericReply(Server *irc, const int &fd, std::string code, std::string replyMsg)
{
	std::string reply = ":" + irc->getHostname() + " " + code + " "
						+ irc->getUserByFd(fd)->getNickname() + " " + replyMsg;
	return (reply);
}


reply = ": serverhostname 311 nickname reply"