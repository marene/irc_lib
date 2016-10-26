/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 14:54:47 by marene            #+#    #+#             */
/*   Updated: 2016/10/26 15:53:38 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

SocketInterface::SocketInterface()
{}

SocketInterface::~SocketInterface()
{}

TcpClientAbstract::TcpClientAbstract(): _hostName("localhost"), _port(4242)
{
	std::cout << this->_hostName << ":" << this->_port << std::endl;
}

TcpClientAbstract::TcpClientAbstract(std::string const& hostName, int32_t port): _hostName(hostName), _port(port)
{
	std::cout << this->_hostName << ":" << this->_port << std::endl;
}

TcpClientAbstract::~TcpClientAbstract()
{}

IrcClientSocket::IrcClientSocket(): TcpClientAbstract::TcpClientAbstract()
{}

IrcClientSocket::IrcClientSocket(std::string const& hostName, int32_t port): TcpClientAbstract::TcpClientAbstract(hostName, port)
{}

ssize_t			IrcClientSocket::send(std::string const& buff)
{
	std::cout << "sending [" << buff << "]" << std::endl;
	return buff.size();
}

ssize_t			IrcClientSocket::receive(std::string& buff)
{
	buff = "Hello World";
	return buff.size();
}
