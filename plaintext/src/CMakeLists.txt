#
# $Id: CMakeLists.txt 292 2012-06-16 13:03:03Z alba $
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

CHECK_FUNCTION_EXISTS(snprintf HAVE_SNPRINTF)
IF(NOT(HAVE_SNPRINTF))
  # Microsoft's Visual Studio provides _snprintf, but not snprintf
  CHECK_FUNCTION_EXISTS(_snprintf HAVE__SNPRINTF)
ENDIF()

# --------------------------------------------------------------------
# Target definitions
# --------------------------------------------------------------------
IF(WITH_SEPARATE_LIBS)
  STRING(REPLACE "plaintext/src/" ""
    plaintext_SOURCES_SRC "${plaintext_SOURCES}")
  ADD_LIBRARY(${plaintext_LIB_NAME} ${plaintext_SOURCES_SRC})

  GET_TARGET_PROPERTY(libtype ${plaintext_LIB_NAME} TYPE)
  ADD_DEFINITIONS(-Dgiglgu_plaintext_IS_${libtype})

  INSTALL(
    TARGETS ${plaintext_LIB_NAME}
    ARCHIVE DESTINATION ${ARCHIVE_DIR}
    LIBRARY DESTINATION ${LIB_DIR}
    RUNTIME DESTINATION ${BIN_DIR}
  )
ENDIF()

# --------------------------------------------------------------------
# Configuration file
# --------------------------------------------------------------------

# Create config.h - this statement must come after all SETs
# Private files don't get installed.
CONFIGURE_FILE(
  private.h.cmake
  ${CMAKE_BINARY_DIR}/include/giglgu/plaintext/private.h
)

