/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 13:22:58 by marene            #+#    #+#             */
/*   Updated: 2016/11/07 14:15:19 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <iostream>
# include <string>
# include <cerrno>
# include "Buffer.hpp"

class		SocketInterface
{
	public:
		SocketInterface();
		virtual ~SocketInterface();

	public:
		virtual ssize_t				send(std::string const& buff) = 0;
		virtual ssize_t				receive(std::string& buff) = 0;
		virtual bool				isConnected() const = 0;
};

class		TcpClientSocketAbstract: public SocketInterface
{
	protected:
		std::string				_hostname;
		in_addr_t				_addr;
		int32_t					_port;
		bool					_state;
		int						_socket;
		static const size_t		_packetsize = 512;
	public:
		TcpClientSocketAbstract(); /// _hostname defaults to "localhost", _port defaults to 4242
		TcpClientSocketAbstract(std::string const& hostname, int32_t port);
		~TcpClientSocketAbstract();

		int						getSocketFd() const;
		bool					connect();
};

class		IrcClientSocket: public TcpClientSocketAbstract
{
	public:
		IrcClientSocket();
		IrcClientSocket(std::string const& hostname, int32_t port);

		ssize_t					send(std::string const& buff);
		ssize_t					receive(std::string& buff);
		bool					isConnected() const;
};

#endif /* !SOCKET_HPP */
