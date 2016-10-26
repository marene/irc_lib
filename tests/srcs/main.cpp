#include "irclib.hpp"

int		main(void)
{
	std::string		buff = std::string("Test");
	std::string		hostname = std::string("Toto");
	IrcClientSocket* socket = new IrcClientSocket::IrcClientSocket(hostname, 8080);

	socket->send(buff);
	socket->receive(buff);
	std::cout << "received : " << buff << std::endl;
	return (0);
}
