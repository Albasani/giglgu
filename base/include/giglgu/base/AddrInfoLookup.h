/*
 * $Id: AddrInfoLookup.h 198 2012-02-15 23:07:21Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_BASE_ADDRINFOLOOKUP_H
#define GIGLGU_BASE_ADDRINFOLOOKUP_H

#include <giglgu/base/Component.h>
#include <giglgu/base/SocketError.h>

#include <iostream>	// std::ostream

struct sockaddr;
struct addrinfo;

namespace giglgu {

class AddrInfo;

/**
 * @class AddrInfoLookup
 * @brief Wrapper for getaddrinfo
 * @note
 * On Windows the symbol "GetAddrInfo" is defined in file "WS2tcpip.h".
 * It resolves to either "getaddrinfo" or "GetAddrInfoW".
 */
class GIGLGU_BASE_EXPORT AddrInfoLookup
{
private:
   /* return value of getaddrinfo */
  int m_error;
  void* m_info;

public:
  AddrInfoLookup(const char* node, const char* service);
  AddrInfoLookup(const char* node, const char* service, const AddrInfo& hints);
  ~AddrInfoLookup();
  
  bool isValid() const { return m_error == 0; }
  AddrInfoError getLastError() const { return AddrInfoError(m_error); }

  const addrinfo* getAddrInfo(size_t index = 0) const;
  std::ostream& inspect(std::ostream&) const;

private:
  bool lookup(const char *node, const char *service, const AddrInfo* hints);
};

} // namespace giglgu

#endif
