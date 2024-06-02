/*
 * $Id: LogConditionMap.cpp 307 2012-06-18 17:12:52Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/logging/LogConditionMap.h>
#include <giglgu/logging/LogCondition.h>
#include <giglgu/logging/LogCondition.inc>

using namespace giglgu::logging;

LogConditionMap::LogConditionMap()
: m_map(0)
{
  m_map = new TMap;
  LogCondition::ForEachR(*this);
}

LogConditionMap::~LogConditionMap()
{
  delete m_map; m_map = 0;
}

void LogConditionMap::operator()(const LogCondition& lc)
{
  const TMap::value_type v(
    std::string(lc.getName()),
    &lc
  );
  const std::pair<TMapCI, bool> result = m_map->insert(v);

  // const std::pair<TMapCI, bool> result = m_map->insert(&lc);
  if (!result.second)
  {
    std::cerr
    << "Ignored duplicate LogCondition \"" << lc.getName()
    << "\" (" << static_cast<const void*>(&lc)
    << ")\n";
  }
}

std::ostream& LogConditionMap::inspect(std::ostream& strm) const
{
  TMapCI end = m_map->end();
  for(TMapCI i = m_map->begin(); i != end; ++i)
  {
    const LogCondition& lc = *(i->second);
    lc.inspect(strm);
  }
  return strm;
}

