#
# $Id: CMakeLists.txt 285 2012-06-13 21:26:10Z alba $
#
# Copyright 2011-2012 Alexander Bartolich
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

install(
  FILES
  AddrInfoError.h
  Component.h
  CondAttr.h
  Cond.h
  CriticalSection.h
  DynamicLoaderError.h
  DynamicLoader.h
  ErrnoError.h
  MutexAttr.h
  Mutex.h
  ThreadAttr.h
  Thread.h
  ThreadLocalStorage.h
  DESTINATION include/giglgu/posix
)
