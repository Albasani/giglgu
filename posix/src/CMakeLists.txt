#
# $Id: CMakeLists.txt 285 2012-06-13 21:26:10Z alba $
#
# Copyright 2011-2012 Alexander Bartolich
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

# --------------------------------------------------------------------
# Platform checks
# --------------------------------------------------------------------

SET(CMAKE_REQUIRED_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")
SET(CMAKE_EXTRA_INCLUDE_FILES unistd.h pthread.h)

CHECK_FUNCTION_EXISTS(pthread_getattr_np HAVE_pthread_getattr_np)
CHECK_FUNCTION_EXISTS(pthread_mutexattr_getrobust HAVE_pthread_mutexattr_getrobust)
CHECK_FUNCTION_EXISTS(pthread_mutexattr_getrobust_np HAVE_pthread_mutexattr_getrobust_np)
CHECK_FUNCTION_EXISTS(pthread_mutexattr_setrobust HAVE_pthread_mutexattr_setrobust)
CHECK_FUNCTION_EXISTS(pthread_mutexattr_setrobust_np HAVE_pthread_mutexattr_setrobust_np)

CHECK_TYPE_SIZE(clockid_t SIZEOF_clockid_t)
CHECK_TYPE_SIZE(pthread_attr_t SIZEOF_pthread_attr_t)
CHECK_TYPE_SIZE(pthread_condattr_t SIZEOF_pthread_condattr_t)
CHECK_TYPE_SIZE(pthread_cond_t SIZEOF_pthread_cond_t)
CHECK_TYPE_SIZE(pthread_key_t SIZEOF_pthread_key_t)
CHECK_TYPE_SIZE(pthread_mutexattr_t SIZEOF_pthread_mutexattr_t)
CHECK_TYPE_SIZE(pthread_mutex_t SIZEOF_pthread_mutex_t)
CHECK_TYPE_SIZE(pthread_once_t SIZEOF_pthread_once_t)
CHECK_TYPE_SIZE(pthread_t SIZEOF_pthread_t)

# <arpa/inet.h>  ... inet_ntop
# <netdb.h>      ... struct addrinfo
# <netinet/in.h> ... struct sockaddr_storage
# <sys/socket.h> ... socklen_t
SET(CMAKE_EXTRA_INCLUDE_FILES unistd.h sys/socket.h netinet/in.h arpa/inet.h netdb.h)
CHECK_FUNCTION_EXISTS(inet_ntop HAVE_inet_ntop)
CHECK_TYPE_SIZE("struct sockaddr_storage" SIZEOF_sockaddr_storage)
CHECK_TYPE_SIZE("struct addrinfo" SIZEOF_addrinfo)
CHECK_TYPE_SIZE(socklen_t SIZEOF_socklen_t)

SET(CMAKE_EXTRA_INCLUDE_FILES)
SET(CMAKE_REQUIRED_LIBRARIES)

# --------------------------------------------------------------------
# Target definitions
# --------------------------------------------------------------------

IF(WITH_SEPARATE_LIBS)
  STRING(REPLACE "posix/src/" "" posix_SOURCES_SRC "${posix_SOURCES}")
  ADD_LIBRARY(${posix_LIB_NAME} ${posix_SOURCES_SRC})

  TARGET_LINK_LIBRARIES(
    ${posix_LIB_NAME}
    ${CMAKE_THREAD_LIBS_INIT}
    dl
  )

  INSTALL(
    TARGETS ${posix_LIB_NAME}
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
  ${CMAKE_BINARY_DIR}/include/giglgu/posix/config.h
)
CONFIGURE_FILE(
  private.h.cmake
  ${CMAKE_BINARY_DIR}/include/giglgu/posix/private.h
)

# Only the public file gets installed.
install(
  FILES
  ${CMAKE_BINARY_DIR}/include/giglgu/posix/config.h
  DESTINATION include/giglgu/base
)

# --------------------------------------------------------------------
# END
# --------------------------------------------------------------------
