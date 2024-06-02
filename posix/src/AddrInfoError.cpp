/*
 * $Id: AddrInfoError.cpp 119 2012-02-07 18:35:25Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/posix/AddrInfoError.h>

#include <netdb.h>	// gai_strerror

using namespace giglgu::posix;

void AddrInfoError::printString(std::ostream& strm) const
{
  strm << gai_strerror(m_error);
}

std::string AddrInfoError::getString() const
{
  return gai_strerror(m_error);
}
