#
# $Id: CMakeLists.txt 224 2012-02-18 21:08:21Z alba $
#
# Copyright 2012 Alexander Bartolich
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

install(
  FILES
  AddrInfo.h
  AddrInfoLookup.h
  AddrToString.h
  Component.h
  NameInfo.h
  SocketAddr.h
  SocketDscr.h
  SocketError.h
  WsaStartup.h
  DESTINATION include/giglgu/base
)