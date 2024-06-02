/*
 * $Id: config.h.cmake 279 2012-06-02 10:03:36Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_WINDOWS_CONFIG_H
#define GIGLGU_WINDOWS_CONFIG_H

#cmakedefine HAVE_PTHREAD_H             @CMAKE_HAVE_PTHREAD_H@

#cmakedefine SIZEOF_CRITICAL_SECTION    @SIZEOF_CRITICAL_SECTION@
#cmakedefine SIZEOF_WSADATA             @SIZEOF_WSADATA@
#cmakedefine SIZEOF_sockaddr_storage    @SIZEOF_sockaddr_storage@
#cmakedefine SIZEOF_addrinfo            @SIZEOF_addrinfo@

#endif
