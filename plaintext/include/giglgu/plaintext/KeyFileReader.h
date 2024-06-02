/*
 * $Id: KeyFileReader.h 294 2012-06-16 14:17:56Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_PLAINTEXT_KEYFILEREADER_H
#define GIGLGU_PLAINTEXT_KEYFILEREADER_H

#include <giglgu/plaintext/Component.h>

#include <iostream>	// std::ostream
#include <map>		// std::map
#include <string>	// std::string

namespace giglgu { namespace PlainText {

class KeyFileReader
{
public:
  KeyFileReader();
  ~KeyFileReader();
  void read(std::istream& strm, const std::string& separator,
    const std::string& trimSet);
  void dump(std::ostream& strm);

  const std::string& getString(const std::string& key) const;
  long getLong(const std::string& key) const;

private:
  // disabled, no implementation
  KeyFileReader(const KeyFileReader&);
  KeyFileReader& operator=(const KeyFileReader&);

private:
  typedef std::map<std::string, std::string> TMap;
  typedef TMap::const_iterator TMapCI;
  typedef TMap::iterator TMapI;
  TMap m_map;
};

}} // namespace

#endif
