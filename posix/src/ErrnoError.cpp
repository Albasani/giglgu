/*
 * $Id: ErrnoError.cpp 74 2012-02-06 00:11:53Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/posix/ErrnoError.h>

#include <cstring>  // strerror

using namespace giglgu::posix;

void ErrnoError::printString(std::ostream& strm) const
{
  strm << strerror(m_error);
}

std::string ErrnoError::getString() const
{
  return strerror(m_error);
}
