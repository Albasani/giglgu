/*
 * $Id: NameInfo.h 136 2012-02-10 16:17:55Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_BASE_NAMEINFO_H
#define GIGLGU_BASE_NAMEINFO_H

#include <giglgu/base/Component.h>
#include <giglgu/base/SocketError.h>

#include <string>	// std::string

namespace giglgu {

class SocketAddr;

/**
 * @class NameInfo
 * @brief Wrapper for getnameinfo
 */
class GIGLGU_BASE_EXPORT NameInfo
{
private:
  /** return value of by getnameinfo */
  int m_error;
  /*
   * Directly using an instance of std::string as member is problematic
   * on Windows. See warning C4251.
   */
  std::string* m_host;
  std::string* m_serv;
public:
  /** Calls resolve(addr, numeric). */
  NameInfo(const SocketAddr& addr, bool numeric = false);
  ~NameInfo();
  
  bool isValid() const { return m_error == 0; }
  AddrInfoError getLastError() const { return AddrInfoError(m_error); }
  
  /** @throws std::runtime_error if m_serv is 0. */
  const std::string& getServ() const;
  
  /** @throws std::runtime_error if m_host is 0. */
  const std::string& getHost() const;
  
  bool resolve(const SocketAddr& addr, bool numeric = false);
};

} // namespace giglgu

#endif