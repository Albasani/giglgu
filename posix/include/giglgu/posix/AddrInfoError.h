/*
 * $Id: AddrInfoError.h 119 2012-02-07 18:35:25Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_POSIX_ADDRINFOERROR_H
#define GIGLGU_POSIX_ADDRINFOERROR_H

#include <iostream>
#include <string>

namespace giglgu { namespace posix {

/**
 * @class AddrInfoError
 * @brief Wrapper for gai_strerror(int)
 */

class AddrInfoError
{
private:
  int m_error;

public:
  AddrInfoError(int error) : m_error(error) {}

  int getError() const { return m_error; }
  bool isError() const { return m_error != 0; }
  bool isEINTR() const { return false; }
  void printString(std::ostream& strm) const;
  std::string getString() const;
};

inline std::ostream& operator<<(std::ostream& strm, const AddrInfoError& e)
{
  e.printString(strm); return strm;
}

}} // namespace

#endif /* #ifndef GIGLGU_POSIX_ADDRINFOERROR_H */
