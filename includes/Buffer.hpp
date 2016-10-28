/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Buffer.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 13:23:02 by marene            #+#    #+#             */
/*   Updated: 2016/10/28 17:56:56 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_HPP
# define BUFFER_HPP

# include <string>
# include <array>
# include <iostream>

class		BufferInterface
{
	public:
		BufferInterface();
		virtual ~BufferInterface();

		virtual ssize_t				write(char c) = 0;
		virtual ssize_t				write(std::string const& str) = 0;
		virtual ssize_t				read(char& c) = 0;
		virtual ssize_t				read(std::string& str) = 0;
};

class		CircularBufferAbstract: public BufferInterface
{
	protected:
		size_t			_buffSize;
		size_t			_start;
		size_t			_end;
		size_t			_size;
		char*			_buff;

		virtual size_t	_strstr(std::string const& sub) const = 0;

	public:
		CircularBufferAbstract();
		CircularBufferAbstract(size_t size);
		virtual ~CircularBufferAbstract();

		virtual size_t				getBuffSize() const;
		virtual size_t				getStart() const;
		virtual size_t				getEnd() const;
		virtual size_t				getSize() const;
		virtual bool				isEmpty() const;
		virtual bool				isFull() const;
		virtual bool				isFull(size_t size) const;
};

class		IrcCircularBuffer: public CircularBufferAbstract
{
	protected:
		size_t						_strstr(std::string const& sub) const;
	public:
		IrcCircularBuffer();
		IrcCircularBuffer(size_t size);
		~IrcCircularBuffer();

		ssize_t						write(char c);
		ssize_t						write(std::string const& str);
		ssize_t						read(char& c);
		ssize_t						read(std::string& str);

		static const std::string	crlf;
};

#endif /* !BUFFER_HPP */
