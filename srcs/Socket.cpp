/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 14:54:47 by marene            #+#    #+#             */
/*   Updated: 2016/10/28 17:30:17 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

SocketInterface::SocketInterface()
{}

SocketInterface::~SocketInterface()
{}

TcpClientSocketAbstract::TcpClientSocketAbstract(): TcpClientSocketAbstract::TcpClientSocketAbstract("localhost", 4242)
{
}

TcpClientSocketAbstract::TcpClientSocketAbstract(std::string const& hostname, int32_t port): _hostname(hostname), _port(port), _state(false)
{
	struct protoent*		proto;

	if ((proto = getprotobyname("tcp")) != NULL)
	{
		if ((this->_socket = socket(PF_INET, SOCK_STREAM, proto->p_proto)) > 0)
			this->_state = this->_connect();
	}
}

TcpClientSocketAbstract::~TcpClientSocketAbstract()
{}

bool			TcpClientSocketAbstract::_connect()
{
	struct sockaddr_in	address;
	struct in_addr		**in_addr;
	struct hostent		*hostent;

	if ((hostent = gethostbyname(this->_hostname.c_str())) != NULL)
	{
		in_addr = (struct in_addr**)hostent->h_addr_list;
		this->_hostname = inet_ntoa(**in_addr);
	}
	this->_addr = inet_addr(this->_hostname.c_str());
	if (this->_addr != INADDR_NONE)
	{
		address.sin_family = PF_INET;
		address.sin_port = htons(this->_port);
		address.sin_addr.s_addr = this->_addr;
		if (connect(this->_socket, (const struct sockaddr*)&address, sizeof(address)) != -1)
			return true;
	}
	return false;
}

int				TcpClientSocketAbstract::getSocketFd() const
{
	return this->_socket;
}

IrcClientSocket::IrcClientSocket(): TcpClientSocketAbstract::TcpClientSocketAbstract()
{}

IrcClientSocket::IrcClientSocket(std::string const& hostname, int32_t port): TcpClientSocketAbstract::TcpClientSocketAbstract(hostname, port)
{}

ssize_t			IrcClientSocket::send(std::string const& buff)
{
	std::cout << "sending [" << buff << "]" << std::endl;
	return ::send(this->_socket, buff.c_str(), buff.size(), 0);
}

ssize_t			IrcClientSocket::receive(std::string& s)
{
	char		buff[this->_packetsize + 1];
	ssize_t		ret;

	if ((ret = recv(this->_socket, buff, this->_packetsize, 0)) > 0)
	{
		buff[ret] = '\0';
		s = buff;
	}
	return ret;
}

bool			IrcClientSocket::isConnected() const
{
	return this->_state;
}
