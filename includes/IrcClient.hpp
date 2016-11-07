/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 15:36:32 by marene            #+#    #+#             */
/*   Updated: 2016/11/07 18:04:59 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <regex>
# include <sys/select.h>
# include "Socket.hpp"
# include "Buffer.hpp"

class		IrcClientAbstract
{
	protected:
		TcpClientSocketAbstract*		_socket;
		CircularBufferAbstract*			_buff;
		CircularBufferAbstract*			_readBuff;
		fd_set							_readfds;
		fd_set							_writefds;
		int								_nfds;
		std::string						_ping;

		static const int				stdinfileno = 0;
		static const int				stdoutfileno = 1;

		virtual void					_setnfds() = 0;
	public:
		IrcClientAbstract();
		IrcClientAbstract(std::string const& hostname, int port);
		virtual ~IrcClientAbstract();

		bool							cmdUser(std::string const& username, std::string const& hostname,
											std::string const& servername, std::string const& realname);
		bool							cmdNick(std::string const& nick);
		bool							cmdPong();
		bool							isConnected() const;
		bool							connect();
		virtual void					select() = 0;
		virtual void					run() = 0;
};

class		IrcClientBot: public IrcClientAbstract
{
	protected:
		void							_setnfds();
		void							_send();
		void							_receive();
		void							_parseMsg(std::string const& msg);
	public:
		IrcClientBot();
		IrcClientBot(std::string const& hostname, int port);
		~IrcClientBot();

		void							select();
		void							run();

};

#endif /* !CLIENT_HPP */
