#
# $Id: CMakeLists.txt 268 2012-05-18 16:05:15Z alba $
#
# Copyright 2012 Alexander Bartolich
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

add_executable(TestWinError TestWinError.cpp)
TARGET_LINK_LIBRARIES(TestWinError
  ${windows_LIB_NAME}
  ${OS_SOCKET_LIBRARY})
add_test(NAME TestWinError COMMAND TestWinError)

add_executable(TestCriticalSection TestCriticalSection.cpp)
TARGET_LINK_LIBRARIES(TestCriticalSection
  ${windows_LIB_NAME}
  ${OS_SOCKET_LIBRARY})
add_test(NAME TestCriticalSection COMMAND TestCriticalSection)

install(
  TARGETS TestCriticalSection TestWinError
  RUNTIME DESTINATION ${BIN_DIR}/test
)
