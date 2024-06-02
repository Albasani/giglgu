/*
 * $Id: SocketError.h 120 2012-02-07 18:38:07Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_BASE_SOCKETERROR_H
#define GIGLGU_BASE_SOCKETERROR_H

#ifdef _WIN32
# include <giglgu/windows/WsaError.h>
#else
# include <giglgu/posix/ErrnoError.h>
# include <giglgu/posix/AddrInfoError.h>
#endif

namespace giglgu {

#ifdef _WIN32
  typedef giglgu::windows::WsaError SocketError;
  typedef giglgu::windows::WsaError AddrInfoError;
#else
  typedef giglgu::posix::ErrnoError SocketError;
  typedef giglgu::posix::AddrInfoError AddrInfoError;
#endif

} // namespace

#endif /* #ifndef GIGLGU_BASE_SOCKETERROR_H */
