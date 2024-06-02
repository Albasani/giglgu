/*
 * $Id: Component.h 220 2012-02-17 23:36:07Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_BASE_COMPONENT_H
#define GIGLGU_BASE_COMPONENT_H

#include <giglgu/base/config.h>

#if defined (_WIN32)
# include <giglgu/windows/config.h>
#else
# include <giglgu/posix/config.h>
#endif

#if defined (_WIN32)
# if defined(giglgu_base_EXPORTS)
#   define GIGLGU_BASE_EXPORT   __declspec(dllexport)
# elif defined(giglgu_base_IS_SHARED_LIBRARY)
#   define GIGLGU_BASE_EXPORT   __declspec(dllimport)
# endif
#endif

#if !defined(GIGLGU_BASE_EXPORT)
# define GIGLGU_BASE_EXPORT
#endif

#endif /* #ifndef GIGLGU_BASE_COMPONENT_H */
