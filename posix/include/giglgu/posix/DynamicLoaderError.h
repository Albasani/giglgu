/*
 * $Id: DynamicLoaderError.h 287 2012-06-14 18:29:52Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_POSIX_DYNAMICLOADERERROR_H
#define GIGLGU_POSIX_DYNAMICLOADERERROR_H

#include <iostream>	// std::ostream
#include <string>	// std::string

namespace giglgu { namespace posix {

/**
 * @class DynamicLoaderError
 * @brief Wrapper for dlerror
 */
class DynamicLoaderError
{
private:
  std::string m_msg;

public:
  /* Initializes m_msg with dlerror() */
  DynamicLoaderError();

  ~DynamicLoaderError();

  bool isError() const { return m_msg.length() != 0; }
  const std::string& getString() const { return m_msg; }
  void printString(std::ostream& strm) const;
};

inline std::ostream& operator<<(
  std::ostream& strm,
  const DynamicLoaderError& dle)
{
  dle.printString(strm); return strm;
}

}} // namespace

#endif /* #ifndef GIGLGU_POSIX_DYNAMICLOADERERROR_H */
