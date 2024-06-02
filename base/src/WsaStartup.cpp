/*
 * $Id: WsaStartup.cpp 148 2012-02-11 11:35:31Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/base/WsaStartup.h>

#if defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <winsock2.h>
#endif

#include <iomanip>	// std::hex

using namespace giglgu;

#define M_DATA \
  reinterpret_cast<WSADATA&>(m_data)
#define M_DATA_CONST \
  reinterpret_cast<const WSADATA&>(m_data)

WsaStartup::WsaStartup(unsigned versionRequested)
: m_error(0)
{
#if defined(_WIN32)
  m_error = ::WSAStartup(versionRequested, &M_DATA);
#endif
}

WsaStartup::~WsaStartup()
{
#if defined(_WIN32)
  m_error = ::WSACleanup();
#endif
}

std::ostream& WsaStartup::inspect(std::ostream& strm) const
{
#if defined(_WIN32)
  const WSADATA& d = M_DATA_CONST;
  strm
  << "wVersion=0x" << std::hex << d.wVersion << std::dec
  << "\nwHighVersion=0x" << std::hex << d.wHighVersion << std::dec
  << "\nszDescription=" << d.szDescription
  << "\nszSystemStatus=" << d.szSystemStatus
  << "\niMaxSockets=" << d.iMaxSockets
  << "\niMaxUdpDg=" << d.iMaxUdpDg
  << '\n'
  ;  
#endif
  return strm;
}