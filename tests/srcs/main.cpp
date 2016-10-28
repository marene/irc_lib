#include "irclib.hpp"

int		main(void)
{
	std::string			buff = std::string("Test");
	std::string			hostname = std::string("irc.root-me.org");
	int					port = 6667;
	IrcClientAbstract*	client = new IrcClientBot::IrcClientBot(hostname, port);

	if (!client->isConnected())
		std::cout << "client did not connect! :(" << std::endl;
	else
		std::cout << "client connected!" << std::endl;
	return (client->isConnected());
}
