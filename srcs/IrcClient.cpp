/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 15:43:14 by marene            #+#    #+#             */
/*   Updated: 2016/10/27 19:37:36 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "IrcClient.hpp"

IrcClientAbstract::IrcClientAbstract(): IrcClientAbstract::IrcClientAbstract("localhost", 4242)
{}

IrcClientAbstract::IrcClientAbstract(std::string const& hostname, int port)
{
	std::string		s;

	this->_socket = new IrcClientSocket(hostname, port);
	this->_buff = new IrcCircularBuffer();
	if (this->_socket->isConnected())
	{
		while (1)
		{
			if (this->_socket->receive(s) > 0)
			std::cout << "received: " << s << std::endl;
		}
	}
	else
		std::cout << "No connection!" << std::endl;
}

IrcClientAbstract::~IrcClientAbstract()
{
	delete this->_socket;
	delete this->_buff;
}

bool			IrcClientAbstract::isConnected() const
{
	return this->_socket->isConnected();
}
