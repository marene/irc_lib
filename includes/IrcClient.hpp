/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 15:36:32 by marene            #+#    #+#             */
/*   Updated: 2016/10/27 20:17:02 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include "Socket.hpp"
# include "Buffer.hpp"

class		IrcClientAbstract
{
	protected:
		TcpClientSocketAbstract*		_socket;
		CircularBufferAbstract*			_buff;
	public:
		IrcClientAbstract();
		IrcClientAbstract(std::string const& hostname, int port);
		~IrcClientAbstract();

		bool							cmdUser(std::string const& username, std::string const& hostname,
											std::string const& servername, std::string const& realname);
		bool							cmdNick(std::string const& nick);
		bool							isConnected() const;
};

#endif /* !CLIENT_HPP */
