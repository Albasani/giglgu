#
# $Id: CMakeLists.txt 302 2012-06-17 20:30:50Z alba $
#
# Copyright 2012 Alexander Bartolich
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

install(
  FILES
  Atomic.h
  Component.h
  CriticalSection.h
  DynamicLoader.h
  Thread.h
  ThreadLocalStorage.h
  WinError.h
  WsaError.h
  DESTINATION include/giglgu/windows
)
