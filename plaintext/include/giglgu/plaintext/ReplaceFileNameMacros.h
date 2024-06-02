/*
 * $Id: ReplaceFileNameMacros.h 254 2012-02-23 09:31:51Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_PLAINTEXT_REPLACEFILENAMEMACROS_H
#define GIGLGU_PLAINTEXT_REPLACEFILENAMEMACROS_H

#include <giglgu/plaintext/Component.h>

#include <string>	// std::string

namespace giglgu { namespace PlainText {

GIGLGU_PLAINTEXT_EXPORT void
ReplaceFileNameMacros(std::string& s);

}} // namespace

#endif
