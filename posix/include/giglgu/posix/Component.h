/*
 * $Id: Component.h 101 2012-02-07 08:59:05Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_POSIX_COMPONENT_H
#define GIGLGU_POSIX_COMPONENT_H

#include <iostream>

namespace giglgu { namespace posix {

/**
 * The default error stream is std::cerr.
 * Use this function to redirect messages.
 * @note Not thread-safe.
 */
void setErrorStream(std::ostream*);

}} // namespace

#endif /* #ifndef GIGLGU_POSIX_COMPONENT_H */
