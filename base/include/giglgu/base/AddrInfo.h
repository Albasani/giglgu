/*
 * $Id: AddrInfo.h 204 2012-02-16 15:13:19Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_BASE_ADDRINFO_H
#define GIGLGU_BASE_ADDRINFO_H

#include <giglgu/base/Component.h>

#include <string>   // std::string
#include <iostream> // std::ostream

struct addrinfo;

namespace giglgu {

class SocketAddr;

/**
 * @class AddrInfo
 * @brief Wrapper for struct addrinfo.
 */
class GIGLGU_BASE_EXPORT AddrInfo
{
private:
  // reserve space for struct addrinfo.
  long m_addr[
    (SIZEOF_addrinfo + sizeof(long) - 1) / sizeof(long)
  ];

public:
  /**
   * On Windows: AF_INET6 = 23
   * On Linux  : AF_INET6 = 10
   */
  enum Family {
    FamilyUNSPEC,
    FamilyUNIX,
    FamilyINET,
    FamilyINET6
  };
  enum Type {
    TypeUnspec = 0,
    TypeSTREAM = 1,
    TypeDGRAM  = 2
  };
  enum Flag {
    FlagAddrConfig,
    FlagAll,
    FlagCanonName,
    FlagNumericHost,
    FlagNumericServ,
    FlagPassive,
    FlagV4Mapped
  };

public:
  AddrInfo(Family = FamilyUNSPEC, Type = TypeUnspec);
  ~AddrInfo();

  const addrinfo& getAddrInfo() const;
  
  AddrInfo& setFamily(Family = FamilyUNSPEC);
  AddrInfo& setType(Type t = TypeUnspec);
  AddrInfo& setFlag(Flag f, bool set);

  AddrInfo& setNumericHost(bool set) { return setFlag(FlagNumericHost, set); }
  AddrInfo& setNumericServ(bool set) { return setFlag(FlagNumericServ, set); }
  AddrInfo& setPassive(bool set) { return setFlag(FlagPassive, set); }
  AddrInfo& setCanonName(bool set) { return setFlag(FlagCanonName, set); }
  AddrInfo& setAddrConfig(bool set) { return setFlag(FlagAddrConfig, set); }
  AddrInfo& setV4Mapped(bool set) { return setFlag(FlagV4Mapped, set); }
  AddrInfo& setAll(bool set) { return setFlag(FlagAll, set); }

  static const char* GetSockTypeName(int);
  static unsigned GetFamilyValue(Family);
  static unsigned GetFlagValue(Flag);
  static void PrintFlagNames(
    std::ostream& strm,
    unsigned value,
    const char* separator = 0);

  std::ostream& inspect(std::ostream& strm) const;
  static std::ostream& Inspect(std::ostream&, const addrinfo&);
};

inline const addrinfo& AddrInfo::getAddrInfo() const
{
  return *reinterpret_cast<const addrinfo*>(&m_addr);
}

inline std::ostream& AddrInfo::inspect(std::ostream& strm) const
{
  return Inspect(strm, getAddrInfo());
}

} // namespace giglgu

#endif
