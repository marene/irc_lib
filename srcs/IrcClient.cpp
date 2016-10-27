/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 15:43:14 by marene            #+#    #+#             */
/*   Updated: 2016/10/27 20:21:16 by marene           ###   ########.fr       */
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
	if (this->isConnected())
	{
		this->cmdNick("marene");
		this->cmdUser("bot", "bot", "bot", "bot");
	}
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

bool			IrcClientAbstract::cmdUser(std::string const& username, std::string const& hostname, std::string const& servername, std::string const& realname)
{
	this->_buff->write("USER ");
	this->_buff->write(' ');
	this->_buff->write(username);
	this->_buff->write(' ');
	this->_buff->write(hostname);
	this->_buff->write(' ');
	this->_buff->write(servername);
	this->_buff->write(" :");
	this->_buff->write(realname);
	this->_buff->write("\r\n");
	return true;
}

bool							IrcClientAbstract::cmdNick(std::string const& nick)
{
	this->_buff->write("NICK ");
	this->_buff->write(nick);
	this->_buff->write("\r\n");
	return true;
}
