/*
 * $Id: TestCondVar.cpp 264 2012-05-01 12:47:33Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/posix/CondAttr.h>
#include <giglgu/posix/Cond.h>

#include <iostream>	// std::cout
#include <iomanip>	// std::hex

using namespace giglgu::posix;

static void setClock(CondAttr& ca, CondAttr::ClockID id)
{
  std::cout << "setClock(" << CondAttr::GetClockName(id) << ")\n";
  ca.setClock(id);
  ca.inspect(std::cout);
}

int main(const int argc, const char** argv)
{
  CondAttr ca;
  ca.inspect(std::cout);

  ca.setPShared(true);
  ca.inspect(std::cout);

  ca.setPShared(false);
  ca.inspect(std::cout);

  setClock(ca, CondAttr::REALTIME);
  setClock(ca, CondAttr::MONOTONIC);
  setClock(ca, CondAttr::PROCESS_CPUTIME_ID);
  setClock(ca, CondAttr::THREAD_CPUTIME_ID);

  Cond cond;

  return 0;
}
