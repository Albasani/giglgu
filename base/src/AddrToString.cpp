/*
 * $Id: AddrToString.cpp 274 2012-06-01 21:44:18Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/base/AddrToString.h>

#include <giglgu/plaintext/private.h>   // sprintf
#include <giglgu/plaintext/hexdump.h>

#if defined(_WIN32)
# include <winsock2.h>
# include <ws2tcpip.h>                  // sockaddr_in6
#else
# include <giglgu/posix/config.h>       // HAVE_inet_ntop
# include <sys/socket.h>                // struct sockaddr
# include <netinet/in.h>                // struct sockaddr_sin
# include <arpa/inet.h>                 // inet_ntop
#endif

#include <cassert>                      // assert
#include <cstdio>                       // sprintf

using namespace giglgu;

AddrToString::AddrToString()
: m_buffer(new std::string)
, m_dst(*m_buffer)
, m_error(0)
{}

AddrToString::AddrToString(std::string& dst)
: m_buffer(0)
, m_dst(dst)
, m_error(0)
{}

AddrToString::~AddrToString()
{
  delete m_buffer;
}

#if !defined(_WIN32)
static int appendSA(const sockaddr_in& sin, std::string& dst)
{
  char sz[0x100];
#if HAVE_inet_ntop
  if (!inet_ntop(sin.sin_family, &sin.sin_addr, sz, sizeof(sz)))
    return errno;
  dst.append(sz);
#else
  dst.append(inet_ntoa(sin.sin_addr));
#endif
  dst.append(sz, sprintf(sz, ":%u", sin.sin_port));
  return 0;
}
#endif

#if !defined(_WIN32)
static int appendSIN(const sockaddr_in6& sin6, std::string& dst)
{
  char sz[0x100];
#if HAVE_inet_ntop
  if (!inet_ntop(sin6.sin6_family, &sin6.sin6_addr, sz, sizeof(sz)))
    return errno;
  dst.append(1, '[');
  dst.append(sz);
#else
  dst.append(1, '[');
  giglgu::PlainText::hexdump(dst, &sin6.sin6_addr, sizeof(sin6.sin6_addr), ':');
#endif
  dst.append(sz, sprintf(sz, "]:%u", sin6.sin6_port));
  return 0;
}
#endif

bool AddrToString::append(const void* addr, size_t addrLen)
{
  const sockaddr& sa = *static_cast<const sockaddr*>(addr);

#ifdef _WIN32
  char sz[0x100];
  DWORD stringLen = sizeof(sz);
  assert(static_cast<DWORD>(addrLen) == addrLen);
  m_error = WSAAddressToString(
    const_cast<sockaddr*>(&sa), static_cast<DWORD>(addrLen),
    0, sz, &stringLen
  );
  if (m_error != 0)
    return false;
  m_dst.append(sz, stringLen);
  return true;
#else
  if (addrLen >= sizeof(sa))
  {
    switch(sa.sa_family)
    {
      case AF_INET:
        if (addrLen >= sizeof(sockaddr_in))
        {
          m_error = appendSA(*static_cast<const sockaddr_in*>(addr), m_dst);
          return m_error == 0;
        }
        break;
      case AF_INET6:
        if (addrLen >= sizeof(sockaddr_in6))
        {
          m_error = appendSIN(*static_cast<const sockaddr_in6*>(addr), m_dst);
          return m_error == 0;
        }
        break;    
      default: break;
    }
  }
  m_error = EINVAL;
  return false;
#endif
}

const char* AddrToString::GetFamilyName(int f)
{
#define CASE(f) case f: return #f;
  switch(f)
  {
    CASE(AF_UNIX)
    CASE(AF_INET)
    CASE(AF_INET6)
    CASE(AF_IPX)
#if !defined(_WIN32)
    CASE(AF_NETLINK)
    CASE(AF_X25)
    CASE(AF_AX25)
    CASE(AF_ATMPVC)
    CASE(AF_PACKET)
#endif
    CASE(AF_APPLETALK)
    default: return 0;
  }
#undef CASE
}
