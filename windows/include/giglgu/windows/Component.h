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
#ifndef GIGLGU_WINDOWS_COMPONENT_H
#define GIGLGU_WINDOWS_COMPONENT_H

#include <giglgu/windows/config.h>

#if defined (_WIN32)
# if defined(giglgu_windows_EXPORTS)
#   define GIGLGU_WINDOWS_EXPORT   __declspec(dllexport)
# elif defined(giglgu_windows_IS_SHARED_LIBRARY)
#   define GIGLGU_WINDOWS_EXPORT   __declspec(dllimport)
# endif
#endif

#if !defined(GIGLGU_WINDOWS_EXPORT)
# define GIGLGU_WINDOWS_EXPORT
#endif

#endif /* #ifndef GIGLGU_WINDOWS_COMPONENT_H */