#
# $Id: CMakeLists.txt 224 2012-02-18 21:08:21Z alba $
#
# Copyright 2011-2012 Alexander Bartolich
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

IF(WIN32)
  SET(SOCKET_LIBRARY wsock32.lib ws2_32.lib
    CACHE INTERNAL "Libraries required to use sockets.")
ENDIF(WIN32)

add_executable(EchoServer EchoServer.cpp)
target_link_libraries(
  EchoServer
  ${base_LIB_NAME}
)

add_executable(TestAddrInfo TestAddrInfo.cpp)
target_link_libraries(
  TestAddrInfo
  ${base_LIB_NAME}
)
add_test(NAME TestAddrInfo COMMAND TestAddrInfo)

add_executable(TestDefine TestDefine.cpp)
target_link_libraries(
  TestDefine
  ${SOCKET_LIBRARY}
  ${CMAKE_THREAD_LIBS_INIT}
)
add_test(NAME TestDefine COMMAND TestDefine)

install(
  TARGETS
    EchoServer
    TestAddrInfo
    TestDefine
  RUNTIME DESTINATION ${BIN_DIR}/test
)
