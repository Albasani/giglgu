/*
 * $Id: AddrToString.h 157 2012-02-12 23:43:54Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_BASE_ADDRTOSTRING_H
#define GIGLGU_BASE_ADDRTOSTRING_H

#include <giglgu/base/Component.h>
#include <giglgu/base/SocketError.h>

#include <iostream>	// std::ostream
#include <string>	// std::string

namespace giglgu {

/**
 * @class AddrToString
 * @brief Convert socket address to a string representation.
 */
class GIGLGU_BASE_EXPORT AddrToString
{
private:
  std::string* m_buffer;
  std::string& m_dst;
  int m_error;

public:
  AddrToString();
  AddrToString(std::string& dst);
  ~AddrToString();

  bool append(const void* addr, size_t addrLen);
  bool isValid() const { return m_error != 0; }
  SocketError getError() const { return SocketError(m_error); }
  const std::string& getString() const { return m_dst; }
  
  static const char* GetFamilyName(int family);
};

inline std::ostream& operator<<(
  std::ostream& strm,
  const AddrToString& ats)
{ return strm << ats.getString(); }

} // namespace

#endif /* #ifndef GIGLGU_BASE_SOCKETADDR_H */
