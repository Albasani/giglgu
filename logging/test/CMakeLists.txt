#
# $Id: CMakeLists.txt 244 2012-02-20 21:49:19Z alba $
#
# Copyright 2012 Alexander Bartolich
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

ADD_EXECUTABLE(TestForwarding TestForwarding.cpp)
TARGET_LINK_LIBRARIES(TestForwarding ${logging_LIB_NAME})
ADD_TEST(NAME TestForwarding COMMAND TestForwarding)

ADD_EXECUTABLE(TestLogAssert TestLogAssert.cpp)
TARGET_LINK_LIBRARIES(TestLogAssert ${logging_LIB_NAME})
ADD_TEST(NAME TestLogAssert COMMAND TestLogAssert)

ADD_EXECUTABLE(TestLogCondition TestLogCondition.cpp)
TARGET_LINK_LIBRARIES(TestLogCondition ${logging_LIB_NAME})
ADD_TEST(NAME TestLogCondition COMMAND TestLogCondition)

ADD_EXECUTABLE(TestLogFile TestLogFile.cpp)
TARGET_LINK_LIBRARIES(TestLogFile ${logging_LIB_NAME})
ADD_TEST(NAME TestLogFile COMMAND TestLogFile)

install(
  TARGETS
    TestLogCondition
    TestLogFile
    TestLogAssert
  RUNTIME DESTINATION ${BIN_DIR}/test
)
