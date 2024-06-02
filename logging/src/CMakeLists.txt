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
# Target definitions
# --------------------------------------------------------------------

IF(WITH_SEPARATE_LIBS)
  STRING(REPLACE "logging/src/" "" logging_SOURCES "${logging_SOURCES}")
  ADD_LIBRARY(${logging_LIB_NAME} ${logging_SOURCES})

  GET_TARGET_PROPERTY(libtype giglgu_logging TYPE)
  ADD_DEFINITIONS(-Dgiglgu_logging_IS_${libtype})

  TARGET_LINK_LIBRARIES(
    ${logging_LIB_NAME}
    ${plaintext_LIB_NAME}
    ${posix_LIB_NAME}
    ${windows_LIB_NAME}
  )

  INSTALL(
    TARGETS ${logging_LIB_NAME}
    ARCHIVE DESTINATION ${ARCHIVE_DIR}
    LIBRARY DESTINATION ${LIB_DIR}
    RUNTIME DESTINATION ${BIN_DIR}
  )
ENDIF(WITH_SEPARATE_LIBS)
