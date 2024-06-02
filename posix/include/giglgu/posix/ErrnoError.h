/*
 * $Id: ErrnoError.h 146 2012-02-11 11:08:24Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_POSIX_ERRNOERROR_H
#define GIGLGU_POSIX_ERRNOERROR_H

#include <iostream>	// std::ostream
#include <string>	// strerror
#include <cerrno>	// errno

namespace giglgu { namespace posix {

/**
 * @class ErrnoError
 * @brief Wrapper for errno and strerror
 */
class ErrnoError
{
private:
  int m_error;

public:
  ErrnoError() : m_error(errno) {}
  ErrnoError(int error) : m_error(error) {}

  int getError() const { return m_error; }
  bool isError() const { return m_error != 0; }
  bool isEINTR() const { return m_error == EINTR; }
  void printString(std::ostream& strm) const;
  std::string getString() const;
};

inline std::ostream& operator<<(std::ostream& strm, const ErrnoError& e)
{
  e.printString(strm); return strm;
}

}} // namespace

#endif /* #ifndef GIGLGU_POSIX_ERRNOERROR_H */
