/*
 * $Id: NameInfo.cpp 197 2012-02-15 21:14:58Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/base/NameInfo.h>

#include <giglgu/base/SocketAddr.h>

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <winsock2.h>
# include <ws2tcpip.h>
#else
# include <netdb.h>	// NI_NUMERICHOST
#endif

#include <stdexcept>	// std::runtime_error

using namespace giglgu;

NameInfo::NameInfo(const SocketAddr& addr, bool numeric)
: m_error(0)
, m_host(0)
, m_serv(0)
{
  resolve(addr, numeric);
}

NameInfo::~NameInfo()
{
  delete m_host; m_host = 0;
  delete m_serv; m_serv = 0;
}

const std::string& NameInfo::getServ() const
{
  if (m_serv == 0)
    throw std::runtime_error("m_serv is 0.");
  return *m_serv;
}

const std::string& NameInfo::getHost() const
{
  if (m_host == 0)
    throw std::runtime_error("m_host is 0.");
  return *m_host;
}

bool NameInfo::resolve(const SocketAddr& addr, bool numeric)
{
  m_error = 0;
  delete m_host; m_host = 0;
  delete m_serv; m_serv = 0;

  char host[0x100];
  char serv[0x20];
  const int flags = numeric ? (NI_NUMERICHOST | NI_NUMERICSERV) : 0;
  m_error = getnameinfo(
    &addr.getSockAddr(),
    addr.getLength(),
    host, sizeof(host),
    serv, sizeof(serv),
    flags
  );
  if (m_error != 0)
    return false;

  m_host = new std::string(host);
  m_serv = new std::string(serv);
  return true;
}
