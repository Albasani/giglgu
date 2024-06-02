/*
 * $Id: ForwardingStream.h 266 2012-05-18 16:04:36Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_LOGGING_LOGBUFFER
#define GIGLGU_LOGGING_LOGBUFFER

#include <giglgu/logging/Component.h>
#include <giglgu/logging/ForwardingSink.h>

#include <sstream>

namespace giglgu { namespace logging {

template< typename _CharT, typename _Traits, typename _Alloc >
class GenericForwardingSB
: public std::basic_stringbuf< _CharT, _Traits, _Alloc >
{
public:
  typedef std::basic_ostream< _CharT, _Traits > StreamType;

private:
  ForwardingSink& m_sink;

public:
  GenericForwardingSB(ForwardingSink& sink)
  : std::basic_stringbuf< _CharT, _Traits, _Alloc >(std::ios_base::out)
  , m_sink(sink)
  {}
  virtual int sync();
};

template< typename _CharT, typename _Traits, typename _Alloc >
int GenericForwardingSB< _CharT, _Traits, _Alloc >::sync()
{
  if (this->pptr())
  {
    if (this->pptr() > this->egptr())
    {
      m_sink.write(this->pbase(), this->pptr() - this->pbase());
      this->seekpos(0, std::ios_base::out);
    }
  }
  return 0;
}

template< typename _CharT, typename _Traits, typename _Alloc >
class GenericForwardingStream
: public std::basic_ostream< _CharT, _Traits >
{
public:
  typedef std::basic_ostream< _CharT, _Traits > StreamType;
  typedef GenericForwardingSB< _CharT, _Traits, _Alloc > BufferType;

private:
  BufferType m_buffer;

public:
  /**
   * @note
   * The CTOR of the base class is called before m_buffer is initialized.
   * This works only if the base class CTOR does not call any methods
   * of m_buffer.
   */
  GenericForwardingStream(ForwardingSink& sink)
  : std::basic_ostream< _CharT, _Traits >(&m_buffer)
  , m_buffer(sink)
  {}

  BufferType* rdbuf() const { return const_cast<BufferType*>(&m_buffer); }
};

typedef GIGLGU_LOGGING_EXPORT_TEMPLATE
GenericForwardingSB< char, std::char_traits< char >, std::allocator< char > >
ForwardingSB;

typedef GIGLGU_LOGGING_EXPORT_TEMPLATE
GenericForwardingStream< char, std::char_traits< char >, std::allocator< char > >
ForwardingStream;

}} // namespace

#endif
