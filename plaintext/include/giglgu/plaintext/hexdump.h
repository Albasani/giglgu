/*
 * $Id: hexdump.h 207 2012-02-16 16:46:35Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_PLAINTEXT_HEXDUMP_H
#define GIGLGU_PLAINTEXT_HEXDUMP_H

#include <giglgu/plaintext/Component.h>

#include <string>	// std::string

namespace giglgu { namespace PlainText {

GIGLGU_PLAINTEXT_EXPORT
void hexdump(
  std::string& dst,
  const void* src,
  size_t srcLen,
  char separator = ' '
);

}} // namespace

#endif
