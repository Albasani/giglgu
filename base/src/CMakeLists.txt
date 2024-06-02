#
# $Id: CMakeLists.txt 226 2012-02-18 21:19:18Z alba $
#
# Copyright 2012 Alexander Bartolich
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

# --------------------------------------------------------------------
# Platform checks
# --------------------------------------------------------------------

TEST_BIG_ENDIAN(HAVE_BIG_ENDIAN)

# --------------------------------------------------------------------
# Target definitions
# --------------------------------------------------------------------

IF(WITH_SEPARATE_LIBS)
  STRING(REPLACE "base/src/" "" base_SOURCES "${base_SOURCES}")
  ADD_LIBRARY(${base_LIB_NAME} ${base_SOURCES})

  GET_TARGET_PROPERTY(libtype giglgu_base TYPE)
  ADD_DEFINITIONS(-Dgiglgu_base_IS_${libtype})

  TARGET_LINK_LIBRARIES(
    ${base_LIB_NAME}
    ${plaintext_LIB_NAME}
    ${posix_LIB_NAME}
    ${windows_LIB_NAME}
    ${logging_LIB_NAME}
  )

  INSTALL(
    TARGETS ${base_LIB_NAME}
    ARCHIVE DESTINATION ${ARCHIVE_DIR}
    LIBRARY DESTINATION ${LIB_DIR}
    RUNTIME DESTINATION ${BIN_DIR}
  )
ENDIF(WITH_SEPARATE_LIBS)

# --------------------------------------------------------------------
# Configuration file
# --------------------------------------------------------------------

# Create config.h - this statement must come after all SETs
CONFIGURE_FILE(
  config.h.cmake
  ${CMAKE_BINARY_DIR}/include/giglgu/base/config.h
)

# Only the public file gets installed.
INSTALL(
  FILES
  ${CMAKE_BINARY_DIR}/include/giglgu/base/config.h
  DESTINATION include/giglgu/base
)
