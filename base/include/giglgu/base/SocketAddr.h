/*
 * $Id: SocketAddr.h 197 2012-02-15 21:14:58Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_BASE_SOCKETADDR_H
#define GIGLGU_BASE_SOCKETADDR_H

#include <giglgu/base/Component.h>

#include <iostream>	// std::ostream

struct sockaddr;

namespace giglgu {

class AddrInfoLookup;

/**
 * @class SocketAddr
 * @brief Wrapper for sockaddr_in and sockaddr_in6
 */
class GIGLGU_BASE_EXPORT SocketAddr
{
public:
#ifdef _WIN32
  typedef int socklen_t;
#else
  typedef unsigned socklen_t;
#endif

public:
  SocketAddr();
  SocketAddr(const void* addr, socklen_t len);
  SocketAddr(const AddrInfoLookup& gai, size_t index);
  ~SocketAddr();

  const sockaddr& getSockAddr() const;
  socklen_t getLength() const { return m_len; }

  bool getPeerName(int socket);
  bool getSockName(int socket);
  int accept(int socket);

  std::ostream& print(std::ostream&) const;
  std::ostream& inspect(std::ostream&) const;

private:
  // resembles struct sockaddr_storage
  char m_addr[0x80];
  socklen_t m_len;
};

inline const sockaddr& SocketAddr::getSockAddr() const
{
  return *reinterpret_cast<const sockaddr*>(&m_addr);
}

inline std::ostream& operator<<(std::ostream& strm, const SocketAddr& sa)
{
  return sa.print(strm);
}

} // namespace

#endif /* #ifndef GIGLGU_BASE_SOCKETADDR_H */
