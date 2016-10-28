/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 15:36:32 by marene            #+#    #+#             */
/*   Updated: 2016/10/28 16:26:49 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <sys/select.h>
# include "Socket.hpp"
# include "Buffer.hpp"

class		IrcClientAbstract
{
	protected:
		TcpClientSocketAbstract*		_socket;
		CircularBufferAbstract*			_buff;
		fd_set							_readfds;
		fd_set							_writefds;
		int								_nfds;

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
		bool							isConnected() const;
		virtual void					select() = 0;
};

class		IrcClientBot: public IrcClientAbstract
{
	protected:
		void							_setnfds();
	public:
		IrcClientBot();
		IrcClientBot(std::string const& hostname, int port);
		~IrcClientBot();

		void							select();
};

#endif /* !CLIENT_HPP */
