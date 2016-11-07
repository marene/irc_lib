/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 15:43:14 by marene            #+#    #+#             */
/*   Updated: 2016/11/07 18:45:28 by marene           ###   ########.fr       */
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
	this->_readBuff = new IrcCircularBuffer();
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

bool			IrcClientAbstract::connect()
{
	return this->_socket->connect();
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

bool							IrcClientAbstract::cmdPong()
{
	this->_buff->write("PONG :");
	this->_buff->write(this->_ping);
	this->_buff->write(IrcCircularBuffer::crlf);
	return true;
}

IrcClientBot::IrcClientBot(): IrcClientBot("localhost", 4242)
{
}

IrcClientBot::IrcClientBot(std::string const& hostname, int port): IrcClientAbstract::IrcClientAbstract(hostname, port)
{
} 

IrcClientBot::~IrcClientBot()
{}

void							IrcClientBot::_setnfds()
{
	this->_nfds = this->_socket->getSocketFd() + 1;
}

void							IrcClientBot::run()
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

void							IrcClientBot::select()
{
	std::string		rec;

	while (1)
	{
		FD_ZERO(&this->_readfds);
		FD_ZERO(&this->_writefds);
		FD_SET(this->_socket->getSocketFd(), &this->_readfds);
		if (this->_buff->isReadable())
			FD_SET(this->_socket->getSocketFd(), &this->_writefds);
		::select(this->_nfds, &this->_readfds, &this->_writefds, NULL /*change that later on*/, NULL /*ditto*/);
		if (FD_ISSET(this->_socket->getSocketFd(), &this->_writefds))
		{
			this->_send();
		}
		else if (FD_ISSET(this->_socket->getSocketFd(), &this->_readfds))
		{
			this->_receive();
		}
	}
}

void							IrcClientBot::_send()
{
	std::string		rec;

	if (this->_buff->read(rec) != -1)
	{
		std::cout << "==> " << rec;
		this->_socket->send(rec);
		rec.erase(0);
	}
}

void							IrcClientBot::_receive()
{
	std::string			rec;

	if (this->_socket->receive(rec) > 0)
		this->_readBuff->write(rec);
	rec.erase(0);
	while (this->_readBuff->isReadable())
	{
		this->_readBuff->read(rec);
		std::cout << "<== " << rec;
		this->_parseMsg(rec);
	}
}

void							IrcClientBot::_parseMsg(std::string const& msg)
{
	std::regex		reg(":([^:]*) +([a-zA-Z0-9]+) +(:([a-zA-Z0-9]+))*");
	std::smatch		subMatches;
	size_t			i = 0;

	if (std::regex_search(msg, subMatches, reg))
	{
		for (i = 0; i < subMatches.size(); ++i)
		{
			std::cout << "\t" << subMatches[i] << std::endl;
		}
	}
	else
	{
		std::cout << "\tnope" << std::endl;
	}
}
