#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <sys/socket.h>
# include <iostream>
# include <string>

class		SocketInterface
{
	public:
		SocketInterface();
		virtual ~SocketInterface();

	public:
		virtual ssize_t				send(std::string const& buff) = 0;
		virtual ssize_t				receive(std::string& buff) = 0;
};

class		TcpClientAbstract: public SocketInterface
{
	private:
		std::string			_hostName;
		int32_t				_port;
	public:
		TcpClientAbstract(); /// _hostName defaults to "localhost", _port defaults to 4242
		TcpClientAbstract(std::string const& hostName, int32_t port);
		~TcpClientAbstract();
};

class		IrcClientSocket: public TcpClientAbstract
{
	public:
		IrcClientSocket();
		IrcClientSocket(std::string const& hostName, int32_t port);
		ssize_t					send(std::string const& buff);
		ssize_t					receive(std::string& buff);
};

#endif /* !SOCKET_HPP */
