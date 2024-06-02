#
# $Id: CMakeLists.txt 218 2012-02-17 22:03:37Z alba $
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
SET(SAFE_CMAKE_REQUIRED_DEFINITIONS "${CMAKE_REQUIRED_DEFINITIONS}")
SET(CMAKE_REQUIRED_DEFINITIONS "${CMAKE_REQUIRED_DEFINITIONS}" "-DWIN32_LEAN_AND_MEAN")
SET(CMAKE_EXTRA_INCLUDE_FILES "windows.h")
  
CHECK_INCLUDE_FILES(winsock2.h HAVE_WINSOCK2_H)
IF(HAVE_WINSOCK2_H)
  SET(CMAKE_EXTRA_INCLUDE_FILES "${CMAKE_EXTRA_INCLUDE_FILES}" "winsock2.h")
ELSE()
  CHECK_INCLUDE_FILES(winsock.h HAVE_WINSOCK_H)
  IF(HAVE_WINSOCK_H)  
    SET(CMAKE_EXTRA_INCLUDE_FILES "${CMAKE_EXTRA_INCLUDE_FILES}" "winsock.h")
  ENDIF()
ENDIF()

CHECK_INCLUDE_FILES(ws2tcpip.h HAVE_WS2TCPIP_H)
IF(HAVE_WS2TCPIP_H)
  SET(CMAKE_EXTRA_INCLUDE_FILES "${CMAKE_EXTRA_INCLUDE_FILES}" "ws2tcpip.h")
ENDIF()  

SET(CMAKE_REQUIRED_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")

CHECK_TYPE_SIZE(CRITICAL_SECTION SIZEOF_CRITICAL_SECTION)
CHECK_TYPE_SIZE(WSADATA SIZEOF_WSADATA)
CHECK_TYPE_SIZE("struct addrinfo" SIZEOF_addrinfo)
CHECK_TYPE_SIZE("struct sockaddr_storage" SIZEOF_sockaddr_storage)

SET(CMAKE_REQUIRED_DEFINITIONS "${SAFE_CMAKE_REQUIRED_DEFINITIONS}")
SET(CMAKE_EXTRA_INCLUDE_FILES)
SET(CMAKE_REQUIRED_LIBRARIES)

# --------------------------------------------------------------------
# Target definitions
# --------------------------------------------------------------------

IF(WITH_SEPARATE_LIBS)
  STRING(REPLACE "windows/src/" "" windows_SOURCES "${windows_SOURCES}")
  ADD_LIBRARY(${windows_LIB_NAME} ${windows_SOURCES})

  GET_TARGET_PROPERTY(libtype giglgu_windows TYPE)
  ADD_DEFINITIONS(-Dgiglgu_windows_IS_${libtype})

  TARGET_LINK_LIBRARIES(
    ${windows_LIB_NAME}
    ${CMAKE_THREAD_LIBS_INIT}
	${OS_SOCKET_LIBRARY}
  )
  INSTALL(
    TARGETS ${windows_LIB_NAME}
    ARCHIVE DESTINATION ${ARCHIVE_DIR}
    LIBRARY DESTINATION ${LIB_DIR}
    RUNTIME DESTINATION ${BIN_DIR}
  )
ENDIF()

# --------------------------------------------------------------------
# Configuration file
# --------------------------------------------------------------------

# Create config.h - this statement must come after all SETs
CONFIGURE_FILE(
  config.h.cmake
  ${CMAKE_BINARY_DIR}/include/giglgu/windows/config.h
)
CONFIGURE_FILE(
  private.h.cmake
  ${CMAKE_BINARY_DIR}/include/giglgu/windows/private.h
)

# Only the public file gets installed.
install(
  FILES
  ${CMAKE_BINARY_DIR}/include/giglgu/windows/config.h
  DESTINATION include/giglgu/windows
)
