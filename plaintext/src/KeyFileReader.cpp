/*
 * $Id: KeyFileReader.cpp 293 2012-06-16 14:17:45Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/plaintext/KeyFileReader.h>

#include <fstream>	// stdd:ifstream
#include <cstdlib>	// strtol

namespace giglgu { namespace PlainText {

using std::string;

KeyFileReader::KeyFileReader()
{}

KeyFileReader::~KeyFileReader()
{}

const std::string& KeyFileReader::getString(const std::string& key) const
{
  return m_map.find(key)->second;
}

long KeyFileReader::getLong(const std::string& key) const
{
  char* endp;
  return strtol(getString(key).c_str(), &endp, 10);
}

void KeyFileReader::read(
  std::istream& strm,
  const std::string& separator, 
  const std::string& trimSet) 
{
  string line;
  for(;;)
  {
    getline(strm, line);
    if (strm.fail())
      return;
    size_t keyLen = line.find(separator);
    if (keyLen == string::npos) { continue; /* no separator */ }
    size_t valuePos = keyLen + separator.length();

    while(
      keyLen > 0 &&
      trimSet.find(line[keyLen - 1]) != string::npos
    ) { keyLen--; }
    while(
      valuePos < line.length() &&
      trimSet.find(line[valuePos]) != string::npos
    ) { valuePos++; }

    string key(line, 0, keyLen);
    string value(line, valuePos);
    m_map[key] = value;
  }
}

void KeyFileReader::dump(std::ostream& strm)
{
  for(TMapCI i = m_map.begin(); i != m_map.end(); ++i)
  {
    strm << i->first << "]=[" << i->second << "]\n";
  }
}

}} // namespace
