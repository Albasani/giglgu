/*
 * $Id: AddrInfoLookup.cpp 198 2012-02-15 23:07:21Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/base/AddrInfoLookup.h>

#include <giglgu/base/AddrInfo.h>
#include <giglgu/base/AddrToString.h>

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <winsock2.h>
# include <ws2tcpip.h>
#else
# include <sys/socket.h>
# include <netdb.h>	// getaddrinfo
#endif

using namespace giglgu;

#define M_INFO \
  reinterpret_cast<struct addrinfo*&>(m_info)
#define M_INFO_CONST \
  static_cast<const struct addrinfo*>(m_info)

AddrInfoLookup::AddrInfoLookup(const char *node, const char *service)
: m_error(0)
, m_info(0)
{
  m_error = getaddrinfo(node, service, 0, &M_INFO);
}

AddrInfoLookup::AddrInfoLookup(const char *node, const char *service,
  const AddrInfo& hints)
: m_error(0)
, m_info(0)
{
  m_error = getaddrinfo(
    node,
    service,
    &hints.getAddrInfo(),
    &M_INFO
  );
}

AddrInfoLookup::~AddrInfoLookup()
{
  if (M_INFO != 0)
    { freeaddrinfo(M_INFO); M_INFO = 0; }
}

std::ostream& AddrInfoLookup::inspect(std::ostream& strm) const
{
  unsigned i = 0;
  const struct addrinfo* ai = M_INFO_CONST;
  while(ai != 0)
  {
    strm << '#' << i++ << '\n';
    AddrInfo::Inspect(strm, *ai);
    ai = ai->ai_next;	
  }
  return strm;
}

const addrinfo* AddrInfoLookup::getAddrInfo(size_t index) const
{
  const struct addrinfo* ai = M_INFO_CONST;
  while(ai != 0)
  {
    if (index-- == 0)
      return ai;
    ai = ai->ai_next;
  }
  return 0;
}
