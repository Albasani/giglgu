/*
 * $Id: TestAddrInfo.cpp 196 2012-02-15 21:08:57Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/base/AddrInfo.h>
#include <giglgu/base/AddrInfoLookup.h>
#include <giglgu/base/SocketAddr.h>
#include <giglgu/base/WsaStartup.h>

#include <iostream>	// std::cout
#include <stdlib.h>	// EXIT_SUCCESS

using namespace giglgu;

static void test(const char* node, const char* serv, AddrInfo& hints)
{
#if 0
  std::cout << "Hints:\n";
  hints.inspect(std::cout); 
  std::cout << '\n';
#endif
  AddrInfoLookup ail(node, serv, hints);
  if (node == 0)
    std::cout << "AddrInfoLookup(0)";
  else
    std::cout << "AddrInfoLookup(\"" << node << "\")";
  if (ail.isValid())
  {
    std::cout << '\n';
    ail.inspect(std::cout);
    std::cout << "SockAddr=" << SocketAddr(ail, 0) << '\n';
  }
  else
    std::cout << " failed: " << ail.getLastError() << '\n';
}

static void test(const char* node, const char* serv)
{
  test(node, serv, 
    AddrInfo().
//    setFamily(AddrInfo::FamilyINET).
//    setAddrConfig(false).
      setType(AddrInfo::TypeSTREAM).
      setPassive(true)
  );
}

int main(const int argc, const char** argv)
{
  WsaStartup wsa;
  if (wsa.isValid())
  {
    wsa.inspect(std::cerr);
  }
  else
  {
    std::cerr << wsa.getLastError();
    return EXIT_FAILURE;
  }

  test(0, "www");
  test("localhost", "www");
  test("1.2.3.4", "567");
#if 0  
  test("ip6-localnet", "www");
  test("ip6-mcastprefix", "www");
  test("ip6-allnodes", "www");
  test("ip6-allrouters", "www");
#endif
  
  return EXIT_SUCCESS;
}
