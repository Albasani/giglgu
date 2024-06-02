/*
 * $Id: Component.h 267 2012-05-18 16:04:51Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_PLAINTEXT_COMPONENT_H
#define GIGLGU_PLAINTEXT_COMPONENT_H

#if defined (_WIN32)
# if defined(giglgu_plaintext_EXPORTS)
#   define GIGLGU_PLAINTEXT_EXPORT   __declspec(dllexport)
# elif defined(giglgu_plaintext_IS_SHARED_LIBRARY)
#   define GIGLGU_PLAINTEXT_EXPORT   __declspec(dllimport)
# endif
#endif

#if !defined(GIGLGU_PLAINTEXT_EXPORT)
# define GIGLGU_PLAINTEXT_EXPORT
#endif

/*
 * Visual Studio requires dllexport/dllimport to instantiate templates
 * in a DLL. For example:
 *
 * typedef GIGLGU_PLAINTEXT_EXPORT
 *   BitName<unsigned, std::ostream, const char*> BasicBitName;
 *
 * However, Intel C++ issues a warning in that case:
 *   #2621: attribute "dllexport" does not apply here
 */
#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
# define GIGLGU_PLAINTEXT_EXPORT_TEMPLATE	GIGLGU_PLAINTEXT_EXPORT
#else
# define GIGLGU_PLAINTEXT_EXPORT_TEMPLATE
#endif

#endif /* #ifndef GIGLGU_PLAINTEXT_COMPONENT_H */
