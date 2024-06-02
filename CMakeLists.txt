######################################################################
#
# $Id: CMakeLists.txt 297 2012-06-16 21:06:10Z alba $
#
# Copyright 2011-2012 Alexander Bartolich
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
######################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(giglgu)
SET(
  GIGLGU_VERSION_STR "0.0.1"
  CACHE INTERNAL "Project version number"
)

# --------------------------------------------------------------------
# OPTIONS
# --------------------------------------------------------------------

SET(HTDOCS_DIR  "" CACHE PATH "Installation directory for CSS files.")
SET(BIN_DIR     "" CACHE PATH "Installation directory for executables.")
SET(LIB_DIR     "" CACHE PATH "Installation directory for libraries.")
SET(ARCHIVE_DIR "" CACHE PATH "Installation directory for static libraries.")

IF(NOT HTDOCS_DIR)
  SET(HTDOCS_DIR "${CMAKE_INSTALL_PREFIX}/share/htdocs"
    CACHE INTERNAL "Absolute PATH")
ENDIF()

IF(NOT BIN_DIR)
  SET(BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin"
    CACHE INTERNAL "Absolute PATH")
ENDIF()

IF(NOT LIB_DIR)
  SET(LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    CACHE INTERNAL "Absolute PATH")
ENDIF()

IF(NOT ARCHIVE_DIR)
  SET(ARCHIVE_DIR "${CMAKE_INSTALL_PREFIX}/lib/static"
    CACHE INTERNAL "Absolute PATH")
ENDIF()

OPTION(WITH_SEPARATE_LIBS "Build individual libraries instead of one." OFF)
OPTION(WITH_TESTING "Enable build and executation of test programs." OFF)

# Set ENABLE_TESTING unconditionally, but define test targets
# only if WITH_TESTING is set.
ENABLE_TESTING()

# --------------------------------------------------------------------
# C++ standard, compiler warnings
# --------------------------------------------------------------------

IF(CMAKE_COMPILER_IS_GNUCC)
  ADD_DEFINITIONS(-std=c++98 -Wall -pedantic)
ENDIF(CMAKE_COMPILER_IS_GNUCC)

IF(MSVC)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS=1)
ENDIF(MSVC)

# --------------------------------------------------------------------
# Platform tests
# --------------------------------------------------------------------

INCLUDE(CheckIncludeFiles)
INCLUDE(CheckFunctionExists)
INCLUDE(CheckTypeSize)
INCLUDE(TestBigEndian)

# Sets CMAKE_HAVE_PTHREAD_H
FIND_PACKAGE(Threads)

IF(WIN32)
  # The result of FIND_LIBRARY is a complete path. Visual Studio 10
  # does not like that. So just use the name, not the result.

  FIND_LIBRARY(WSOCK32_LIBRARY wsock32)
  IF(DEFINED WSOCK32_LIBRARY)
    SET(OS_SOCKET_LIBRARY wsock32.lib ${OS_SOCKET_LIBRARY}
      CACHE INTERNAL "Libraries required to use sockets.")
  ENDIF()
	
  FIND_LIBRARY(WS2_32_LIBRARY ws2_32)
  IF(DEFINED WS2_32_LIBRARY)
    SET(OS_SOCKET_LIBRARY ws2_32.lib ${OS_SOCKET_LIBRARY}
      CACHE INTERNAL "Libraries required to use sockets.")
  ENDIF()
ENDIF()

# --------------------------------------------------------------------
# Shared libraries
# --------------------------------------------------------------------

IF(BUILD_SHARED_LIBS)
  # We cannot use GET_TARGET_PROPERTY on targets that are not
  # yet defined, so just check BUILD_SHARED_LIBS.
  # The following definitions tell executables and other shared
  # libraries that their dependencies are shared libraries.
  # The definitions are added here so that all test programs
  # in sub directories get it.
  ADD_DEFINITIONS(-Dgiglgu_posix_IS_SHARED_LIBRARY)
  ADD_DEFINITIONS(-Dgiglgu_windows_IS_SHARED_LIBRARY)
  ADD_DEFINITIONS(-Dgiglgu_plaintext_IS_SHARED_LIBRARY)
  ADD_DEFINITIONS(-Dgiglgu_logging_IS_SHARED_LIBRARY)
  ADD_DEFINITIONS(-Dgiglgu_base_IS_SHARED_LIBRARY)
ENDIF()

# --------------------------------------------------------------------
# Doxygen
# --------------------------------------------------------------------

# Setting DOXYFILE_EXTRA_SOURCES is tricky, because we need to
# escape the line feeds in the resulting doxyfile.
# SET(DOXYFILE_EXTRA_SOURCES "                                     \\
#   \"${CMAKE_BINARY_DIR}/include/giglgu\"                         \\
#   \"${CMAKE_CURRENT_SOURCE_DIR}/base/include/giglgu/base\"       \\
#   \"${CMAKE_CURRENT_SOURCE_DIR}/posix/include/giglgu/posix\"     \\
#   \"${CMAKE_CURRENT_SOURCE_DIR}/windows/include/giglgu/windows\" \\
# ")

# Anyway, since Doxygen is configured to recursively walk into sub
# directories it's not necessary to set DOXYFILE_EXTRA_SOURCES.
INCLUDE(share/UseDoxygen/UseDoxygen.cmake)

# --------------------------------------------------------------------
# Generated header files
# --------------------------------------------------------------------

# Generated configuration files are placed under CMAKE_BINARY_DIR.
# Add this directory to enable #include <giglgu/base/config.h>
INCLUDE_DIRECTORIES( "${CMAKE_BINARY_DIR}/include" )

# --------------------------------------------------------------------
# POSIX support layer
# --------------------------------------------------------------------

IF(CMAKE_HAVE_PTHREAD_H)
  INCLUDE_DIRECTORIES( "posix/include" )
  SET(
    posix_SOURCES
    posix/src/AddrInfoError.cpp
    posix/src/Component.cpp
    posix/src/CondAttr.cpp
    posix/src/Cond.cpp
    posix/src/CriticalSection.cpp
    posix/src/DynamicLoader.cpp
    posix/src/DynamicLoaderError.cpp
    posix/src/ErrnoError.cpp
    posix/src/MutexAttr.cpp
    posix/src/Mutex.cpp
    posix/src/ThreadAttr.cpp
    posix/src/Thread.cpp
    posix/src/ThreadLocalStorage.cpp
    CACHE INTERNAL "List of source files")
  IF(WITH_SEPARATE_LIBS)
    SET(posix_LIB_NAME giglgu_posix
      CACHE INTERNAL "Name of library containing POSIX support layer")
  ELSE()
    SET(posix_LIB_NAME giglgu_main
      CACHE INTERNAL "Name of library containing POSIX support layer")
  ENDIF()
  ADD_SUBDIRECTORY(posix)
ENDIF()

# --------------------------------------------------------------------
# Windows API support layer
# --------------------------------------------------------------------

IF(WIN32)
  INCLUDE_DIRECTORIES( "windows/include" )
  SET(
    windows_SOURCES
    windows/src/Component.cpp
    windows/src/CriticalSection.cpp
    windows/src/DynamicLoader.cpp
    windows/src/Thread.cpp
    windows/src/ThreadLocalStorage.cpp
    windows/src/WinError.cpp
    windows/src/WsaError.cpp
    CACHE INTERNAL "List of source files"
  )
  IF(WITH_SEPARATE_LIBS)
    SET(windows_LIB_NAME giglgu_windows
      CACHE INTERNAL "Name of library")
  ELSE()
    SET(windows_LIB_NAME giglgu_main
      CACHE INTERNAL "Name of library")
  ENDIF()
  ADD_SUBDIRECTORY(windows)
ENDIF()

# --------------------------------------------------------------------
# Plain text processing
# --------------------------------------------------------------------

INCLUDE_DIRECTORIES( "plaintext/include" )
SET(
  plaintext_SOURCES
  plaintext/src/hexdump.cpp
  plaintext/src/KeyFileReader.cpp
  plaintext/src/ReplaceFileNameMacros.cpp
  CACHE INTERNAL "List of source files"
)
IF(WITH_SEPARATE_LIBS)
  SET(plaintext_LIB_NAME giglgu_plaintext
    CACHE INTERNAL "Name of library containing plain text processing")
ELSE()
  SET(plaintext_LIB_NAME giglgu_main
    CACHE INTERNAL "Name of library containing plain text processing")
ENDIF()
ADD_SUBDIRECTORY(plaintext)

# --------------------------------------------------------------------
# Logging
# --------------------------------------------------------------------

INCLUDE_DIRECTORIES( "logging/include" )
SET(
  logging_SOURCES
  logging/src/BadNullStream.cpp
  logging/src/ForwardingSink.cpp
  logging/src/LogCondition.cpp
  logging/src/LogConditionMap.cpp
  logging/src/LogFile.cpp
  logging/src/LogStream.cpp
  CACHE INTERNAL "List of source files"
)
IF(WITH_SEPARATE_LIBS)
  SET(logging_LIB_NAME giglgu_logging CACHE INTERNAL "Name of library")
ELSE()
  SET(logging_LIB_NAME giglgu_main CACHE INTERNAL "Name of library")
ENDIF()
ADD_SUBDIRECTORY(logging)

# --------------------------------------------------------------------
# Base
# --------------------------------------------------------------------

INCLUDE_DIRECTORIES( "base/include" )
SET(
  base_SOURCES
  base/src/AddrInfo.cpp
  base/src/AddrInfoLookup.cpp
  base/src/AddrToString.cpp
  base/src/NameInfo.cpp
  base/src/SocketAddr.cpp
  base/src/SocketDscr.cpp
  base/src/WsaStartup.cpp
  CACHE INTERNAL "List of source files"
)
IF(WITH_SEPARATE_LIBS)
  SET(base_LIB_NAME giglgu_base CACHE INTERNAL "Name of library")
ELSE()
  SET(base_LIB_NAME giglgu_main CACHE INTERNAL "Name of library")
ENDIF()
ADD_SUBDIRECTORY(base)

# --------------------------------------------------------------------
# Main
# --------------------------------------------------------------------

IF(NOT(WITH_SEPARATE_LIBS))

  ADD_LIBRARY(
    giglgu_main
    ${posix_SOURCES}
    ${windows_SOURCES}
    ${plaintext_SOURCES}
    ${logging_SOURCES}
    ${base_SOURCES}
  )

  TARGET_LINK_LIBRARIES(
    giglgu_main
    ${CMAKE_THREAD_LIBS_INIT}
	  ${OS_SOCKET_LIBRARY}
  )

  INSTALL(
    TARGETS giglgu_main
    ARCHIVE DESTINATION ${ARCHIVE_DIR}
    LIBRARY DESTINATION ${LIB_DIR}
    RUNTIME DESTINATION ${BIN_DIR}
  )

  # Using GET_TARGET_PROPERTY is more correct than checking the value
  # of BUILD_SHARED_LIBS, but yields the same result.
  GET_TARGET_PROPERTY(libtype giglgu_main TYPE)
  IF(libtype STREQUAL "SHARED_LIBRARY")
    ADD_DEFINITIONS(-Dgiglgu_posix_EXPORTS)
    ADD_DEFINITIONS(-Dgiglgu_windows_EXPORTS)
    ADD_DEFINITIONS(-Dgiglgu_plaintext_EXPORTS)
    ADD_DEFINITIONS(-Dgiglgu_logging_EXPORTS)
    ADD_DEFINITIONS(-Dgiglgu_base_EXPORTS)
  ENDIF()
ENDIF()

# --------------------------------------------------------------------
# END
# --------------------------------------------------------------------
