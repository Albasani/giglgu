/*
 * $Id: Component.h 266 2012-05-18 16:04:36Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_LOGGING_COMPONENT_H
#define GIGLGU_LOGGING_COMPONENT_H

#if defined (_WIN32)
# include <giglgu/windows/config.h>
#else
# include <giglgu/posix/config.h>
#endif

#if defined (_WIN32)
# if defined(giglgu_logging_EXPORTS)
#   define GIGLGU_LOGGING_EXPORT  __declspec(dllexport)
# elif defined(giglgu_logging_IS_SHARED_LIBRARY)
#   define GIGLGU_LOGGING_EXPORT  __declspec(dllimport)
# endif
#endif

#if !defined(GIGLGU_LOGGING_EXPORT)
# define GIGLGU_LOGGING_EXPORT
#endif

#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
# define GIGLGU_LOGGING_EXPORT_TEMPLATE	GIGLGU_LOGGING_EXPORT
#else
# define GIGLGU_LOGGING_EXPORT_TEMPLATE
#endif

#endif /* #ifndef GIGLGU_LOGGING_COMPONENT_H */
