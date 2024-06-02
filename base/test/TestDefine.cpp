/*
 * $Id: TestDefine.cpp 278 2012-06-02 10:03:18Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <winsock2.h>
# include <ws2tcpip.h>
#else
# include <pthread.h>
# include <sys/socket.h>
# include <netdb.h>	// getaddrinfo
# include <unistd.h>	// STDIN_FILENO
#endif

#include <cstdio>	// printf

#define QUOTE0(s)	#s
#define QUOTE1(s)	QUOTE0(s)
#define QUOTE2(s)	QUOTE1(s)

#define D_HEX(s)	printf("%-20s X : %#x\n", #s, s)
#define D_UINT(s)	printf("%-20s U : %u\n", #s, s)
#define D_INT(s)	printf("%-20s I : %d\n", #s, s)
#define D_STR(s)	printf("%-20s S0: %s\n", #s, s)
#define D_STR1(s)	printf("%-20s S1: %s\n", #s, QUOTE0(s))
#define D_STR2(s)	printf("%-20s S2: %s\n", #s, QUOTE1(s))
#define D_NA(s)		printf("%-20s --: N/A\n", #s)

static void test_FILENO()
{
#if defined(STDIN_FILENO)
  D_INT(STDIN_FILENO);
#else
  D_NA(STDIN_FILENO);
#endif
#if defined(STDOUT_FILENO)
  D_INT(STDOUT_FILENO);
#else
  D_NA(STDOUT_FILENO);
#endif
#if defined(STDERR_FILENO)
  D_INT(STDERR_FILENO);
#else
  D_NA(STDERR_FILENO);
#endif
}

static void test_SOCK()
{
#if defined(SOCK_STREAM)
  D_INT(SOCK_STREAM);
#else
  D_NA(SOCK_STREAM);
#endif
#if defined(SOCK_STREAM)
  D_INT(SOCK_DGRAM);
#else
  D_NA(SOCK_DGRAM);
#endif
}

static void test_AF()
{
  #if defined(AF_UNSPEC)
    D_INT(AF_UNSPEC);
  #else
    D_NA(AF_UNSPEC);
  #endif
  #if defined(AF_UNIX)
    D_INT(AF_UNIX);
  #else
    D_NA(AF_UNIX);
  #endif
  #if defined(AF_INET)
    D_INT(AF_INET);
  #else
    D_NA(AF_INET);
  #endif
  #if defined(AF_INET6)
    D_INT(AF_INET6);
  #else
    D_NA(AF_INET6);
  #endif
}

static void test_SHUT()
{
  #if defined(SD_RECEIVE)
    D_INT(SD_RECEIVE);
  #else
    D_NA(SD_RECEIVE);
  #endif
  #if defined(SD_SEND)
    D_INT(SD_SEND);
  #else
    D_NA(SD_SEND);
  #endif
  #if defined(SD_BOTH)
    D_INT(SD_BOTH);
  #else
    D_NA(SD_BOTH);
  #endif

  #if defined(SHUT_RD)
    D_INT(SHUT_RD);
  #else
    D_NA(SHUT_RD);
  #endif
  #if defined(SHUT_WR)
    D_INT(SHUT_WR);
  #else
    D_NA(SHUT_WR);
  #endif
  #if defined(SHUT_RDWR)
    D_INT(SHUT_RDWR);
  #else
    D_NA(SHUT_RDWR);
  #endif
}

int main(const int argc, const char** argv)
{
  /**
   * On Windows the symbol "GetAddrInfo" is defined in file "WS2tcpip.h".
   * It resolves to either "getaddrinfo" or "GetAddrInfoW".
   */
  #if defined(GetAddrInfo)
    D_STR1(GetAddrInfo);
  #else
    D_NA(GetAddrInfo);
  #endif

  /* Second parameter of function listen. */
  #if defined(SOMAXCONN)
    D_HEX(SOMAXCONN);
    D_INT(SOMAXCONN);
  #else
    D_NA(SOMAXCONN);
  #endif

  /* On Windows, SOCKET_ERROR is the return value in case of error. */
  #if defined(SOCKET_ERROR)
    D_INT(SOCKET_ERROR);
  #else
    D_NA(SOCKET_ERROR);
  #endif

  /* Windows: Return value of TlsAlloc */
  #if defined(TLS_OUT_OF_INDEXES)
    D_INT(TLS_OUT_OF_INDEXES);
  #else
    D_NA(TLS_OUT_OF_INDEXES);
  #endif  

  /* FD_SETSIZE determines maximum number of descriptors in a fd_set. */
  #if defined(FD_SETSIZE)
    D_INT(FD_SETSIZE);
  #else
    D_NA(FD_SETSIZE);
  #endif

  test_FILENO();
  test_SOCK();
  test_AF();
  test_SHUT();
  return 0;
}
