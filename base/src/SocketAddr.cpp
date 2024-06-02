/*
 * $Id: SocketAddr.cpp 273 2012-06-01 21:43:58Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/base/SocketAddr.h>

#include <giglgu/base/AddrToString.h>
#include <giglgu/base/AddrInfoLookup.h>
#include <giglgu/base/SocketError.h>

// #include <giglgu/base/private.h>
#include <giglgu/logging/LogStream.h>

#include <cstring>	// memset
#include <cassert>	// assert

#if defined(_WIN32)
# include <winsock2.h>
# include <ws2tcpip.h>
#else
# include <sys/socket.h> // struct sockaddr
# include <netinet/in.h> // struct sockaddr_sin
# include <arpa/inet.h>  // inet_ntop
# include <netdb.h>      // struct addrinfo
#endif

#define M_ADDR_SA \
  reinterpret_cast<sockaddr&>(m_addr)
#define M_ADDR_SA_CONST \
  reinterpret_cast<const sockaddr&>(m_addr)
#define M_ADDR_SIN_CONST \
  reinterpret_cast<const sockaddr_in&>(m_addr)
#define M_ADDR_SIN6_CONST \
  reinterpret_cast<const sockaddr_in6&>(m_addr)

using namespace giglgu;
using namespace giglgu::logging;

SocketAddr::SocketAddr()
: m_len(0)
{
  memset(&m_addr, 0, sizeof(m_addr));
}

SocketAddr::SocketAddr(const void* addr, socklen_t len)
: m_len(0)
{
  if (len > sizeof(m_addr))
    len = sizeof(m_addr);
  memcpy(m_addr, addr, m_len = len);
}

SocketAddr::SocketAddr(const AddrInfoLookup& ail, size_t index)
: m_len(0)
{
  const addrinfo* ai = ail.getAddrInfo(index);
  if (ai != 0)
  {
    const size_t len = ai->ai_addrlen;
    assert(len <= sizeof(m_addr));
    m_len = static_cast<socklen_t>(len);
    assert(len <= sizeof(m_addr));
    memcpy(m_addr, ai->ai_addr, m_len);
  }
  else
    memset(&m_addr, 0, sizeof(m_addr));
}

SocketAddr::~SocketAddr()
{}

bool SocketAddr::getPeerName(int socket)
{
  m_len = sizeof(m_addr);
  if (-1 != ::getpeername(socket, &M_ADDR_SA, &m_len))
    return true;
	
  const SocketError e;
  LogStream strm;
  strm << "getpeername(" << socket
       << ", " << &M_ADDR_SA
       << ", " << &m_len
       << ") failed, "
       << e << "\n";
  return false;
}

bool SocketAddr::getSockName(int socket)
{
  m_len = sizeof(m_addr);
  if (-1 != ::getsockname(socket, &M_ADDR_SA, &m_len))
    return true;
	
  const SocketError e;
  LogStream strm;
  strm << "getsockname(" << socket
       << ", " << &M_ADDR_SA
       << ", " << &m_len
       << ") failed, "
       << e << "\n";
  return false;
}

int SocketAddr::accept(int socket)
{
  for(;;)
  {
    m_len = sizeof(m_addr);
    const int connectedSocket = ::accept(socket, &M_ADDR_SA, &m_len);
    if (connectedSocket != -1)
      return connectedSocket;

    const SocketError e;
    if (e.isEINTR())
      continue;

    LogStream strm;
    strm << "accept(" << socket
         << ", " << &M_ADDR_SA
         << ", " << &m_len
         << ") failed, "
         << e << "\n";
    return connectedSocket;
  }
}

std::ostream& SocketAddr::inspect(std::ostream& strm) const
{

  strm << "family=";
  const char* familyName = AddrToString::GetFamilyName(M_ADDR_SA_CONST.sa_family);
  if (familyName != 0)
    strm << familyName;
  else
    strm << M_ADDR_SA_CONST.sa_family;
  strm << '\n';
  
  AddrToString ats;
  if (ats.append(m_addr, m_len))
    strm << "addr=" << ats << '\n';
  
  if (M_ADDR_SA_CONST.sa_family == AF_INET6)
  {
    const sockaddr_in6& sin6 = M_ADDR_SIN6_CONST;
    strm << "\nflowinfo=" << ntohl(sin6.sin6_flowinfo);
    strm << "\nscope_id=" << ntohl(sin6.sin6_scope_id) << '\n';
  }
	
  return strm;
}

std::ostream& SocketAddr::print(std::ostream& strm) const
{
  AddrToString ats;
  if (ats.append(m_addr, m_len))
    strm << ats;
  return strm;
}
