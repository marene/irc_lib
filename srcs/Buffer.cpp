/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Buffer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 14:23:14 by marene            #+#    #+#             */
/*   Updated: 2016/10/28 18:00:49 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Buffer.hpp"

BufferInterface::BufferInterface()
{}

BufferInterface::~BufferInterface()
{}

CircularBufferAbstract::CircularBufferAbstract(): _buffSize(2048), _start(0), _end(2048), _size(0)
{
	this->_buff = new char[sizeof(char) * this->_buffSize];
}

CircularBufferAbstract::CircularBufferAbstract(size_t size): _buffSize(size), _start(0), _end(2048), _size(0)
{
	this->_buff = new char[sizeof(char) * this->_buffSize];
}

CircularBufferAbstract::~CircularBufferAbstract()
{
	delete this->_buff;
}

size_t				CircularBufferAbstract::getBuffSize() const
{
	return this->_buffSize;
}

size_t				CircularBufferAbstract::getStart() const
{
	return this->_start;
}

size_t				CircularBufferAbstract::getEnd() const
{
	return this->_end;
}

size_t				CircularBufferAbstract::getSize() const
{
	return this->_size;
}

bool				CircularBufferAbstract::isEmpty() const
{
	return (this->_size == 0);
}

bool				CircularBufferAbstract::isFull() const
{
	return (this->_size == this->_buffSize);
}

bool				CircularBufferAbstract::isFull(size_t size) const
{
	return (this->_size + size >= this->_buffSize);
}

const std::string IrcCircularBuffer::crlf = std::string("\r\n");

IrcCircularBuffer::IrcCircularBuffer(): CircularBufferAbstract::CircularBufferAbstract()
{}

IrcCircularBuffer::IrcCircularBuffer(size_t size): CircularBufferAbstract::CircularBufferAbstract(size)
{}

IrcCircularBuffer::~IrcCircularBuffer()
{
}

size_t				IrcCircularBuffer::_strstr(std::string const& sub) const
{
	size_t		i = 0;
	size_t		index;
	size_t		j;

	if (!this->isEmpty() && sub.size() > 0)
	{
		while (i < this->_size)
		{
			j = 0;
			index = (this->_start + i) % this->_buffSize;
			while (this->_buff[index] == sub[j])
			{
				index = (index + 1) % this->_buffSize;
				++j;
			}
			if (j == sub.size())
				return i + sub.size();
			++i;
		}
	}
	return 0;
}

ssize_t				IrcCircularBuffer::write(char c)
{
	if (!this->isFull(1))
	{
		this->_buff[this->_end] = c;
		this->_end = (this->_end + 1) % this->_buffSize;
		++this->_size;
		return 1;
	}
	else
	{
		return -1;
	}
}

ssize_t				IrcCircularBuffer::write(std::string const& str)
{
	size_t	i = 0;
	if (!this->isFull(str.size()))
	{
		while (i < str.size())
		{
			this->write(str[i]);
			++i;
		}
		return str.size();
	}
	return (-1);
}

ssize_t				IrcCircularBuffer::read(char& c)
{
	if (!this->isEmpty())
	{
		c = this->_start;
		this->_start = (this->_start + 1) % this->_buffSize;
		--this->_size;
		return 1;
	}
	else
		return -1;
}

ssize_t				IrcCircularBuffer::read(std::string& s)
{
	size_t		crlfIndex;
	size_t		retSize;
	char		c;

	if (this->_size > s.size())
	{
		if ((retSize = this->_strstr(IrcCircularBuffer::crlf)) <= this->_size && retSize > 0)
		{
			crlfIndex = retSize;
			while (crlfIndex > 0)
			{
				this->read(c);
				s.push_back(c);
				--crlfIndex;
			}
			return retSize;
		}
	}
	return -1;
}
