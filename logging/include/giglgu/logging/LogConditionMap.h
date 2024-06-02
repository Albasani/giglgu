/*
 * $Id: LogConditionMap.h 310 2012-07-04 15:13:22Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_LOGGING_LOGCONDITIONMAP_H
#define GIGLGU_LOGGING_LOGCONDITIONMAP_H

#include <giglgu/logging/LogCondition.h>

#include <iostream>     // std::ostream
#include <map>          // std::map
#include <string>       // std::string

namespace giglgu { namespace logging {

/**
 * @class LogConditionMap
 */
class GIGLGU_LOGGING_EXPORT LogConditionMap
{
private:
  /*
   * String members of LogCondition are of type const char*. For search
   * operations it is more efficient to use std::string, however. Hence
   * we use std::map instead of std::set.
   */
  typedef std::map<std::string, const LogCondition*> TMap;
  typedef TMap::const_iterator TMapCI;
  typedef TMap::iterator TMapI;

public:
  /**
   * Uses LogCondition::ForEachR to populate m_map.
   */
  LogConditionMap();

  ~LogConditionMap();

  /** Used with LogCondition::ForEachR */
  void operator()(const LogCondition&);

  std::ostream& inspect(std::ostream&) const;
  

private:
  /**
   * @brief Pointer to a TMap.
   * @note
   * Directly using an instance of a template class is problematic on
   * Windows. See warning C4251. Hence we use a pointer.
   */
  TMap* m_map;
};

}} // namespace

#endif /* #ifndef GIGLGU_LOGGING_LOGCONDITIONMAP_H */
