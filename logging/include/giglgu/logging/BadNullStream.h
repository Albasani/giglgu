/*
 * $Id: BadNullStream.h 231 2012-02-19 20:43:37Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_LOGGING_BADNULLSTREAM_H
#define GIGLGU_LOGGING_BADNULLSTREAM_H

#include <iostream>

namespace giglgu { namespace logging {

/**
 * @class BadNullStream
 * @brief Output stream without a stream buffer.
 * The 'badbit' is permanently set. Output goes to nowhere.
 */
class BadNullStream : public std::ostream
{
public:
  BadNullStream();
  ~BadNullStream();
};

}} // namespace

#endif /* #ifndef GIGLGU_LOGGING_BADNULLSTREAM_H */