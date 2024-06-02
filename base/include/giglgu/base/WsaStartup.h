/*
 * $Id: WsaStartup.h 167 2012-02-14 18:33:04Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_BASE_WSASTARTUP_H
#define GIGLGU_BASE_WSASTARTUP_H

#include <giglgu/base/Component.h>
#include <giglgu/base/SocketError.h>

#include <iostream>	// std::ostream

namespace giglgu {

/**
 * @class WsaStartup
 * @brief Wrapper for WSAStartup
 *
 * On Windows you must create an instance of this class to initialize
 * the socket library. On all other platform this class does nothing.
 */
class GIGLGU_BASE_EXPORT WsaStartup
{
private:
  int m_error;

#if defined(_WIN32)
  // reserve space for SIZEOF_WSADATA
  long m_data[
    (SIZEOF_WSADATA + sizeof(long) - 1) / sizeof(long)
  ];
#endif

public:
  WsaStartup(unsigned versionRequested = 0x0202);
  ~WsaStartup();
  
  bool isValid() const { return m_error == 0; }
  SocketError getLastError() const { return SocketError(m_error); }
  std::ostream& inspect(std::ostream&) const;
};

} // namespace

#endif /* #ifndef GIGLGU_BASE_WSASTARTUP_H */
