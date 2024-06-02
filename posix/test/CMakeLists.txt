#
# $Id: CMakeLists.txt 285 2012-06-13 21:26:10Z alba $
#
# Copyright 2011-2012 Alexander Bartolich
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

add_executable(TestCondVar TestCondVar.cpp)
target_link_libraries(
  TestCondVar
  ${posix_LIB_NAME}
)
add_test(NAME TestCondVar COMMAND TestCondVar)

add_executable(TestMutex TestMutex.cpp)
target_link_libraries(
  TestMutex
  ${posix_LIB_NAME}
)
add_test(NAME TestMutex COMMAND TestMutex)

add_executable(TestThreadAttr TestThreadAttr.cpp)
target_link_libraries(
  TestThreadAttr
  ${posix_LIB_NAME}
)
add_test(NAME TestThreadAttr COMMAND TestThreadAttr)

add_executable(TestDynamicLoader TestDynamicLoader.cpp)
target_link_libraries(
  TestDynamicLoader
  ${posix_LIB_NAME}
)
add_test(NAME TestDynamicLoader COMMAND TestDynamicLoader)

install(
  TARGETS TestMutex TestThreadAttr
  RUNTIME DESTINATION ${BIN_DIR}/test
)
