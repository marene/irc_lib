/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 15:43:14 by marene            #+#    #+#             */
/*   Updated: 2016/10/28 18:02:59 by marene           ###   ########.fr       */
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
	this->_buff->write(IrcCircularBuffer::crlf);
	return true;
}

bool							IrcClientAbstract::cmdNick(std::string const& nick)
{
	this->_buff->write("NICK ");
	this->_buff->write(nick);
	this->_buff->write(IrcCircularBuffer::crlf);
	return true;
}

IrcClientBot::IrcClientBot(): IrcClientAbstract::IrcClientAbstract("localhost", 4242)
{
	this->_setnfds();
	FD_ZERO(&this->_readfds);
	FD_ZERO(&this->_writefds);
	if (this->isConnected())
	{
		this->cmdNick("marene");
		this->cmdUser("bot", "bot", "bot", "bot");
		this->select();
	}
}

IrcClientBot::IrcClientBot(std::string const& hostname, int port): IrcClientAbstract::IrcClientAbstract(hostname, port)
{
	this->_setnfds();
	FD_ZERO(&this->_readfds);
	FD_ZERO(&this->_writefds);
	if (this->isConnected())
	{
		this->cmdNick("marene");
		this->cmdUser("bot", "bot", "bot", "bot");
		this->select();
	}
} 

IrcClientBot::~IrcClientBot()
{}

void							IrcClientBot::_setnfds()
{
	this->_nfds = this->_socket->getSocketFd() + 1;
}

void							IrcClientBot::select()
{
	std::string		rec;

	while (1)
	{
		FD_ZERO(&this->_readfds);
		FD_ZERO(&this->_writefds);
		FD_SET(this->_socket->getSocketFd(), &this->_readfds);
		if (!this->_buff->isEmpty())
			FD_SET(this->_socket->getSocketFd(), &this->_writefds);
		::select(this->_nfds, &this->_readfds, &this->_writefds, NULL /*change that later on*/, NULL /*ditto*/);
		if (FD_ISSET(this->_socket->getSocketFd(), &this->_writefds))
		{
//			std::cout << "Write!" <<std::endl;
			if (this->_buff->read(rec) != -1)
			{
				this->_socket->send(rec);
				rec.erase(0);
			}
		}
		else if (FD_ISSET(this->_socket->getSocketFd(), &this->_readfds))
		{
			std::cout << "Read!" <<std::endl;
			this->_socket->receive(rec);
			std::cout << "received : " << rec << std::endl;
		}
	}
}
