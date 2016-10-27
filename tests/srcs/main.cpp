#include "irclib.hpp"

int		main(void)
{
	std::string			buff = std::string("Test");
	std::string			hostname = std::string("irc.root-me.org");
	IrcClientAbstract*	client = new IrcClientAbstract::IrcClientAbstract(hostname, 6667);

	return (client->isConnected());
}
