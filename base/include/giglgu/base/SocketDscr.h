/*
 * $Id: SocketDscr.h 222 2012-02-18 00:03:45Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_BASE_SOCKETDSCR_H
#define GIGLGU_BASE_SOCKETDSCR_H

#include <giglgu/base/Component.h>

#include <cstddef>      // size_t

#if !defined(_WIN32)
# include <unistd.h>    // ssize_t, socklen_t
#endif

struct addrinfo;
struct sockaddr;

namespace giglgu {

class SocketAddr;
class AddrInfoLookup;

/**
 * @class SocketDscr
 * @brief A socket connection (wrapper for socket descriptor)
 */
class GIGLGU_BASE_EXPORT SocketDscr
{
public:
#ifdef _WIN32
  typedef int ssize_t;
  typedef int socklen_t;
#else
  typedef ::ssize_t ssize_t;
#endif

public:
  enum { InvalidDscr = -1 };
  
  /**
   * @brief Values for m_mode. Determines what destructor does.
   * @note Default value set by constructor is "Shutdown".
   */
  enum CloseMode
  {
    Keep,     ///< do nothing
    Close,    ///< close
    Shutdown  ///< shutdown(ShutdownWrite), wait for eof, then close
  };
  
  /**
   * @brief Parameter for shutdownVerbose.
   * @note Values correspond with constants on Windows and Linux.
   * - 0 = SD_RECEIVE = SHUT_RD
   * - 1 = SD_SEND = SHUT_WR
   * - 2 = SD_BOTH = SHUT_RDWR
   */
  enum ShutdownMode
  {
    ShutdownRead,
    ShutdownWrite,
    ShutdownReadWrite
  };

private:
  int m_dscr;
  CloseMode m_mode;

public:
  SocketDscr(int dscr = InvalidDscr);
  SocketDscr(int domain, int type, int protocol);
  
  virtual ~SocketDscr();

  /**
   * @brief Performs socket, bind and listen in one go.
   * @return
   * - On success true is returned and m_dscr is valid.
   * - On error m_dscr is closed and false is returned.
   * @param ai
   * - Pointer to addrinfo, as returned by AddrInfoLookup.
   * - If ai is 0 then false is returned.
   * @note
   * - If m_dscr is already valid then it is released through
   *   closeDscr. If m_mode is Keep, however, then the existing
   *   m_dscr is not released but just replaced.
   */ 
  bool openServer(const addrinfo* ai);
  
  SocketDscr& setCloseMode(CloseMode mode) { m_mode = mode; return *this; }
  int getDscr() const { return m_dscr; }
  bool isValid() const { return m_dscr != InvalidDscr; }
  bool setNonBlock() const { return setNonBlock(m_dscr); }

  ssize_t readVerbose(void* buffer, size_t size);
  ssize_t writeVerbose(const void* buffer, size_t size);

  bool readFullSize(void* buffer, size_t size);
  bool writeFullSize(const void* buffer, size_t size);
  
  /**
   * @param backlog
   * - On Windows, SOMAXCONN is defined as 5 in "WinSock.h"
   *   and as 0x7fffffff in "WinSock2.h".
   * - On Ubuntu 10.04, SOMAXCONN is defined as 128.
   */
  bool listen(int backlog = 4);
  
  bool bind(const SocketAddr& addr);  
  bool bind(const addrinfo& ai);
  
  /**
   * @brief Calls SocketAddr::accept if waitUntilReady returns true.
   */
  int accept(SocketAddr& addr);

public: 
  static bool setNonBlock(int dscr);
  static int socketVerbose(int domain, int type, int protocol);
  static bool bindVerbose(int dscr, const sockaddr& addr, size_t addrLen);
  static ssize_t ReadVerbose(int dscr, void* buffer, size_t size);
  static ssize_t WriteVerbose(int dscr, const void* buffer, size_t size);
  static bool closeVerbose(int dscr);
  static bool shutdownVerbose(int dscr, ShutdownMode how);

protected:
  enum WaitMode { ForRead, ForWrite };

  /** This implementation just returns true. */
  virtual bool waitUntilReady(WaitMode mode);

private:
  SocketDscr(const SocketDscr&); // no implementation
  SocketDscr& operator=(const SocketDscr&); // no implementation
  
  bool closeDscr();
};

inline SocketDscr::ssize_t SocketDscr::readVerbose(void* buffer, size_t size)
{
  return ReadVerbose(m_dscr, buffer, size);
}

inline SocketDscr::ssize_t SocketDscr::writeVerbose(const void* buffer,
  size_t size)
{
  return WriteVerbose(m_dscr, buffer, size);
}

} // namespace

#endif /* #ifndef GIGLGU_BASE_SOCKETDSCR_H */
