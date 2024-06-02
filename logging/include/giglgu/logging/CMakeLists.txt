#
# $Id: CMakeLists.txt 252 2012-02-22 01:31:22Z alba $
#
# Copyright 2012 Alexander Bartolich
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

install(
  FILES
  BadNullStream.h
  Component.h
  CriticalSection.h
  ForwardingSink.h
  ForwardingStream.h 
  LogAssert.h
  LogCondition.h
  LogCondition.inc
  LogFile.h
  LogStream.h
  ThreadLocalStorage.h
  DESTINATION include/giglgu/logging
)
