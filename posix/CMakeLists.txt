#
# $Id: CMakeLists.txt 212 2012-02-17 18:11:34Z alba $
#
# Copyright 2011-2012 Alexander Bartolich
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(include/giglgu/posix)

IF(WITH_TESTING)
  ADD_SUBDIRECTORY(test)
ENDIF()
