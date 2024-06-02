/*
 * $Id: AddrInfo.cpp 205 2012-02-16 16:25:43Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/base/AddrInfo.h>

#include <giglgu/base/AddrToString.h>
#include <giglgu/plaintext/BitName.h>

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <winsock2.h>
# include <ws2tcpip.h>
#else
# include <netdb.h>	// NI_NUMERICHOST
#endif

#include <cassert>	// assert

using namespace giglgu;

#define M_ADDR \
  reinterpret_cast<struct addrinfo&>(m_addr)
#define M_ADDR_CONST \
  reinterpret_cast<const struct addrinfo&>(m_addr)

// compile time assert
#define CTA(n, c) \
  typedef int assert_##n[(c) ? +1 : -1];

AddrInfo::AddrInfo(Family f, Type t)
{
  CTA(TypeUnspec,   (int)TypeUnspec == 0);
  CTA(TypeSTREAM,   (int)TypeSTREAM == (int)SOCK_STREAM);
  CTA(TypeDGRAM,    (int)TypeDGRAM  == (int)SOCK_DGRAM);

  static const struct addrinfo zero = { 0 };
  M_ADDR = zero;
  M_ADDR.ai_flags = (AI_V4MAPPED | AI_ADDRCONFIG);
  M_ADDR.ai_family = GetFamilyValue(f);
  M_ADDR.ai_socktype = t;
}

AddrInfo::~AddrInfo()
{}

AddrInfo& AddrInfo::setFamily(Family f)
{
  M_ADDR.ai_family = GetFamilyValue(f);
  return *this;
}

AddrInfo& AddrInfo::setType(Type t)
{
  M_ADDR.ai_socktype = t;
  return *this;
}

unsigned AddrInfo::GetFlagValue(Flag f)
{
  switch(f)
  {
    case FlagAddrConfig:  return AI_ADDRCONFIG;
    case FlagAll:         return AI_ALL;
    case FlagCanonName:   return AI_CANONNAME;
    case FlagNumericHost: return AI_NUMERICHOST;
    case FlagPassive:     return AI_PASSIVE;
    case FlagV4Mapped:    return AI_V4MAPPED;
    default: assert(0); return 0;
  }
}

unsigned AddrInfo::GetFamilyValue(Family f)
{
  switch(f)
  {
    case FamilyUNSPEC: return AF_UNSPEC;
    case FamilyUNIX  : return AF_UNIX;
    case FamilyINET  : return AF_INET;
    case FamilyINET6 : return AF_INET6;
    default: assert(0); return 0;
  }
}

AddrInfo& AddrInfo::setFlag(Flag f, bool set)
{
  if (set)
    M_ADDR.ai_flags |= GetFlagValue(f);
  else
    M_ADDR.ai_flags &= ~GetFlagValue(f);
  return *this;
}

void AddrInfo::PrintFlagNames(
  std::ostream& strm,
  unsigned value,
  const char* separator)
{
#define F(s)  { s, #s }
  static const giglgu::PlainText::BasicBitName fv[] =
  {
    F(AI_ADDRCONFIG),
    F(AI_ALL),
    F(AI_CANONNAME),
    F(AI_NUMERICHOST),
    F(AI_PASSIVE),
    F(AI_V4MAPPED),
    { 0 }
  };
#undef F
  fv[0].decode(strm, value, separator == 0 ? "|" : separator);
}

const char* AddrInfo::GetSockTypeName(int t)
{
#define CASE(t)	case t: return #t;
  switch(t)
  {
    CASE(SOCK_STREAM)
    CASE(SOCK_DGRAM)
    CASE(SOCK_SEQPACKET)
    CASE(SOCK_RAW)
    CASE(SOCK_RDM)
  #ifdef SOCK_PACKET
    CASE(SOCK_PACKET)
  #endif
    default: return 0;
  }
#undef CASE
}

std::ostream& AddrInfo::Inspect(std::ostream& strm, const addrinfo& ai)
{
  strm << "ai_flags=";
  AddrInfo::PrintFlagNames(strm, ai.ai_flags);
  {
    strm << "\nai_family=";		 
    const char* familyName = AddrToString::GetFamilyName(ai.ai_family);
    if (familyName != 0)
      strm << familyName;
    else
      strm << ai.ai_family;
  }
  {
    strm << "\nai_socktype=";
	  const char* const typeName = GetSockTypeName(ai.ai_socktype);
    if (typeName != 0)
      strm << typeName;
    else
      strm << ai.ai_socktype;
  }
  {
    strm << "\nai_protocol=" << ai.ai_protocol
       	 << "\nai_addrlen=" << ai.ai_addrlen
	       << "\nai_addr="; 
    AddrToString ats;
    ats.append(ai.ai_addr, ai.ai_addrlen);
    strm << ats << '\n';
  }
  if (ai.ai_canonname != 0)
    strm << "ai_canonname=" << ai.ai_canonname << '\n';

  return strm;
}
