/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Buffer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 14:23:14 by marene            #+#    #+#             */
/*   Updated: 2016/10/27 15:33:36 by marene           ###   ########.fr       */
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
	return (this->_size + size <= this->_buffSize);
}

IrcCircularBuffer::IrcCircularBuffer(): CircularBufferAbstract::CircularBufferAbstract()
{}

IrcCircularBuffer::IrcCircularBuffer(size_t size): CircularBufferAbstract::CircularBufferAbstract(size)
{}

IrcCircularBuffer::~IrcCircularBuffer()
{
	delete this->_buff;
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
		return -1;
}

ssize_t				IrcCircularBuffer::read(char& c)
{
	if (!this->isEmpty())
	{
		c = this->_start;
		this->_start = (this->_start + 1) % this->_buffSize;
		return 1;
	}
	else
		return -1;
}
