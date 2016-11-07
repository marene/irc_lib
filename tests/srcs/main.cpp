#include <stdexcept>
#include "irclib.hpp"

int		main(void)
{
	std::string			buff = std::string("Test");
	std::string			hostname = std::string("irc.root-me.org");
	int					port = 6667;
	IrcClientAbstract*	client = new IrcClientBot::IrcClientBot(hostname, port);
 
	try
	{
		client->connect();
		client->run();
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
		delete client;
		client = NULL;
		return 1;
	}
	return (client->isConnected());
}
