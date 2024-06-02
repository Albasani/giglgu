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
#ifndef GIGLGU_POSIX_CONFIG_H
#define GIGLGU_POSIX_CONFIG_H

#cmakedefine HAVE_PTHREAD_H		@CMAKE_HAVE_PTHREAD_H@

#cmakedefine SIZEOF_addrinfo            @SIZEOF_addrinfo@
#cmakedefine SIZEOF_clockid_t           @SIZEOF_clockid_t@
#cmakedefine SIZEOF_pthread_attr_t      @SIZEOF_pthread_attr_t@
#cmakedefine SIZEOF_pthread_condattr_t  @SIZEOF_pthread_condattr_t@
#cmakedefine SIZEOF_pthread_cond_t      @SIZEOF_pthread_cond_t@
#cmakedefine SIZEOF_pthread_key_t       @SIZEOF_pthread_key_t@
#cmakedefine SIZEOF_pthread_mutexattr_t @SIZEOF_pthread_mutexattr_t@
#cmakedefine SIZEOF_pthread_mutex_t     @SIZEOF_pthread_mutex_t@
#cmakedefine SIZEOF_pthread_once_t      @SIZEOF_pthread_once_t@
#cmakedefine SIZEOF_pthread_t           @SIZEOF_pthread_t@
#cmakedefine SIZEOF_sockaddr_storage    @SIZEOF_sockaddr_storage@
#cmakedefine SIZEOF_socklen_t           @SIZEOF_socklen_t@

#endif
