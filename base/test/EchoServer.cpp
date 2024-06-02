/*
 * $Id: EchoServer.cpp 238 2012-02-20 10:34:56Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/logging/LogFile.h>
#include <giglgu/logging/LogStream.h>

#include <giglgu/base/SocketAddr.h>
#include <giglgu/base/SocketDscr.h>
#include <giglgu/base/SocketError.h>
#include <giglgu/base/AddrInfo.h>
#include <giglgu/base/AddrInfoLookup.h>
#include <giglgu/base/NameInfo.h>
#include <giglgu/base/WsaStartup.h>

#include <stdlib.h>	// EXIT_FAILURE

#if defined(_WIN32)
# include <winsock2.h>
# include <ws2tcpip.h>
#else
# include <sys/socket.h> // AF_INET
#endif

#define ENV_LOGFILE   "GIGLGU_LOGFILE"

using namespace giglgu;
using namespace giglgu::logging;

static bool run()
{
  WsaStartup wsa;
  wsa.inspect(std::cerr);
  
  AddrInfoLookup ail(
    0,
    "www",
    AddrInfo().setType(AddrInfo::TypeSTREAM).setPassive(true)
  );
  if (!ail.isValid())
    return false;
    
  SocketDscr serverSock;
  if (!serverSock.openServer(ail.getAddrInfo(0)))
    return false;

  SocketAddr addr; 
  const int peerSock = serverSock.accept(addr);
  if (peerSock == SocketDscr::InvalidDscr)
    return false;

  NameInfo name(addr);
  {
    LogStream strm;
    strm << "peerSock=" << peerSock << "\n";
    addr.inspect(strm);
    strm << "serv=" << name.getServ() << "\n";
    strm << "host=" << name.getHost() << "\n";
  }

  for(;;)
  {
    char buffer[0x100];
    SocketDscr::ssize_t rc = serverSock.readVerbose(buffer, sizeof(serverSock));
    if (rc <= 0)
      break;
    if (!serverSock.writeFullSize(buffer, rc))
      break;
  }
  return true;
}

int main(const int argc, const char** argv)
{
  if (!LogFile::SetupFromEnv(ENV_LOGFILE))
    return EXIT_FAILURE;

  try { run(); }
  catch(const std::exception& exc)
  {
    LogStream strm;
    strm << "Caught std::exception, " << exc.what() << '\n';
  }
  catch(...)
  {
    LogStream strm;
    strm << "Caught unknown exception ...\n";
  }

  LogFile::DeleteInstance();
  return 0;
}
