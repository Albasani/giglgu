/*
 * $Id: SocketDscr.cpp 238 2012-02-20 10:34:56Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/base/SocketDscr.h>

#include <giglgu/base/SocketAddr.h>
#include <giglgu/base/SocketError.h>
#include <giglgu/base/AddrInfoLookup.h>
#include <giglgu/base/AddrToString.h>

#include <giglgu/logging/LogStream.h>

#if defined(_WIN32)
# include <winsock2.h>
# include <ws2tcpip.h>
#else
# include <unistd.h>        // close
# include <fcntl.h>         // O_NONBLOCK
# include <sys/socket.h>    // SHUT_WR
# include <netdb.h>         // struct addrinfo
#endif

using namespace giglgu;
using namespace giglgu::logging;

#ifdef _WIN32
# define CLOSESOCKET    closesocket
#else
# define CLOSESOCKET    close
#endif

#define QUOTE(n)        #n

SocketDscr::SocketDscr(int dscr)
: m_dscr(dscr)
, m_mode(Shutdown)
{
#ifdef _WIN32
  typedef int assert_rd  [ShutdownRead      == SD_RECEIVE     ? 1 : -1];
  typedef int assert_wr  [ShutdownWrite     == SD_SEND        ? 1 : -1];
  typedef int assert_rdwr[ShutdownReadWrite == SD_BOTH        ? 1 : -1];
#else
  typedef int assert_rd  [ShutdownRead      == (int)SHUT_RD   ? 1 : -1];
  typedef int assert_wr  [ShutdownWrite     == (int)SHUT_WR   ? 1 : -1];
  typedef int assert_rdwr[ShutdownReadWrite == (int)SHUT_RDWR ? 1 : -1];
#endif
}

SocketDscr::SocketDscr(int domain, int type, int protocol)
: m_dscr(InvalidDscr)
, m_mode(Shutdown)
{
  m_dscr = socketVerbose(domain, type, protocol);
}

bool SocketDscr::openServer(const addrinfo* ai)
{
  closeDscr();
  if (ai == 0)
    return false;
  m_dscr = socketVerbose(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
  if (m_dscr == InvalidDscr)
    return false;
  if (bindVerbose(m_dscr, *ai->ai_addr, ai->ai_addrlen))
    if (listen())
      return true;
  closeDscr();
  return false;
}

SocketDscr::~SocketDscr()
{
  closeDscr();
}

bool SocketDscr::closeDscr()
{
  if (m_dscr == InvalidDscr)
    return true;
  if (m_mode == Keep)
    return true;
  if (m_mode == Shutdown && shutdownVerbose(m_dscr, ShutdownWrite))
  {
    for(;;)
    {
      char buffer[0x100];
      const ssize_t rc = ::recv(m_dscr, buffer, sizeof(buffer), 0);
      if (rc <= 0)
        break;
      LogStream strm;
      strm << "Discarded " << rc << " bytes on shutdown.\n";
    }
  }
  return closeVerbose(m_dscr);
}

bool SocketDscr::setNonBlock(int dscr)
{
#ifdef _WIN32
  u_long iMode = TRUE;
  if (0 != ioctlsocket(dscr, FIONBIO, &iMode))
  {
    // TODO
  }
#else
  errno = 0;
  long flags = fcntl(dscr, F_GETFL, 0);
  if (flags == -1 && errno != 0)
  {
    const SocketError e;
    LogStream strm;
    strm << "fcntl(" << dscr << ", F_GETFL, 0) failed, " << e << "\n";
    return false;
  }
  flags |= O_NONBLOCK;
  if (-1 == fcntl(dscr, F_SETFL, flags))
  {
    const SocketError e;
    LogStream strm;
    strm << "fcntl(" << dscr << ", F_SETFL, " << flags
         << ") failed, " << e << "\n";
    return false;
  }
#endif
  return true;
}

int SocketDscr::socketVerbose(int domain, int type, int protocol)
{
  const int s = socket(domain, type, protocol);
  if (s == -1)
  {
    SocketError e;
    LogStream strm;
    strm << "socket(" << domain
         << ", " << type
         << ", " << protocol
         << ") failed: " << e << '\n';
  }
  return s;
}

bool SocketDscr::closeVerbose(int dscr)
{
  if (-1 == CLOSESOCKET(dscr))
  {
    const SocketError e;
    LogStream strm;
      strm << QUOTE(CLOSESOCKET) " (" << dscr << ") failed, " << e << "\n";
    return false;
  }
  return true;
}

bool SocketDscr::shutdownVerbose(int dscr, ShutdownMode how)
{
  if (-1 == ::shutdown(dscr, how))
  {
    const SocketError e;
    LogStream strm;
    strm << "shutdown(" << dscr
         << ", " << how
         << ") failed, " << e << "\n";
    return false;
  }
  return true;
}

SocketDscr::ssize_t SocketDscr::ReadVerbose(int dscr, void* buffer, size_t size)
{
  for(;;)
  {
    const ssize_t rc = ::recv(dscr, (char*)buffer, size, 0);
    if (rc > 0)
    {
      LogStream strm;
      strm << "recv(" << dscr
           << ", " << buffer
           << ", " << size
           << ", 0)=" << rc << '\n';
    }
    else if (rc == -1)
    {
      const SocketError e;
      if (e.isEINTR())
        continue;
      LogStream strm;
      strm << "recv(" << dscr
           << ", " << buffer
           << ", " << size
           << ", 0) failed, "
           << e << '\n';
    }
    else if (rc == 0)
    {
      LogStream strm;
      strm << "Unexpected end of file encountered by recv(" << dscr
           << ", " << buffer
           << ", " << size
           << ", 0)\n";
    }
    return rc;
  }
}

bool SocketDscr::waitUntilReady(WaitMode)
{
  return true;
}

bool SocketDscr::readFullSize(void* buffer, size_t size)
{
  while(size > 0)
  {
    if (!waitUntilReady(ForRead))
      return false;
    const ssize_t rc = ReadVerbose(m_dscr, buffer, size);
    if (rc <= 0)
      return false;
    size -= rc;
    buffer = (char*)buffer + rc;
  }
  return true;
}

SocketDscr::ssize_t SocketDscr::WriteVerbose(
  int dscr, const void* buffer, size_t size)
{
  for(;;)
  {
    const ssize_t rc = ::send(dscr, (char*)buffer, size, 0);
    if (rc >= 0)
    {
      LogStream strm;
      strm << "send(" << dscr
           << ", " << buffer
           << ", " << size
           << ", 0)=" << rc << '\n';
    }
    else if (rc == -1)
    {
      const SocketError e;
      if (e.isEINTR())
        continue;
      LogStream strm;
      strm << "send(" << dscr
           << ", " << buffer
           << ", " << size
           << ", 0) failed, "
           << e << '\n';
    }
    return rc;
  }
}

bool SocketDscr::writeFullSize(const void* buffer, size_t size)
{
  while(size > 0)
  {
    if (!waitUntilReady(ForWrite))
      return false;
    const ssize_t rc = WriteVerbose(m_dscr, buffer, size);
    if (rc < 0)
      return false;
    size -= rc;
    buffer = (char*)buffer + rc;
  }
  return true;
}

int SocketDscr::accept(SocketAddr& addr)
{
  return waitUntilReady(ForRead)
  ? addr.accept(getDscr())
  : InvalidDscr;
}

bool SocketDscr::listen(int backlog)
{
  const int result = ::listen(m_dscr, backlog);
  if (result != -1)
    return true;

  SocketError e;
  LogStream strm;
  strm << "listen(" << m_dscr
       << ", " << backlog
       << ") failed, " << e
       ;
  return false;
}

bool SocketDscr::bind(const SocketAddr& addr)
{
  return bindVerbose(m_dscr, addr.getSockAddr(), addr.getLength());
}

bool SocketDscr::bind(const addrinfo& ai)
{
  return bindVerbose(m_dscr, *ai.ai_addr, ai.ai_addrlen);
}

bool SocketDscr::bindVerbose(int dscr, const sockaddr& addr, size_t addrLen)
{
  if (0 == ::bind(dscr, &addr, addrLen))
    return true;
  SocketError e;
  const char* name = AddrToString::GetFamilyName(addr.sa_family);
  LogStream strm;
  strm << "bind(" << dscr
       << ", { ";
  if (name != 0)
    strm << name;
  else
    strm << addr.sa_family;
  strm << " }, " << addrLen
       << ") failed: " << e;
  return false;
}
