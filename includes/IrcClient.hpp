/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 15:36:32 by marene            #+#    #+#             */
/*   Updated: 2016/10/27 18:53:12 by marene           ###   ########.fr       */
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

		bool							isConnected() const;
};

#endif /* !CLIENT_HPP */
