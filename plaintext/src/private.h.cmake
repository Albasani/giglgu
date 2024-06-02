/*
 * $Id: private.h.cmake 224 2012-02-18 21:08:21Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_BASE_PRIVATE_H
#define GIGLGU_BASE_PRIVATE_H

#include <giglgu/base/config.h>

#ifdef _WIN32
# include <giglgu/windows/private.h>
#else
# include <giglgu/posix/private.h>
#endif

#cmakedefine HAVE_SNPRINTF      	@HAVE_SNPRINTF@
#cmakedefine HAVE__SNPRINTF     	@HAVE__SNPRINTF@
#cmakedefine HAVE_BIG_ENDIAN		@HAVE_BIG_ENDIAN@

// #cmakedefine HAVE_ICONV_H       @HAVE_ICONV_H@
// #cmakedefine HAVE_WCHAR_H       @HAVE_WCHAR_H@
// #cmakedefine HAVE_WCSWIDTH      @HAVE_WCSWIDTH@

#if !HAVE_SNPRINTF && HAVE__SNPRINTF
// Microsoft's Visual provides _snprintf instead of snprintf
# define snprintf					_snprintf
#endif

#endif
