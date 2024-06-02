/*
 * $Id: TestMutex.cpp 73 2012-02-06 00:04:12Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/posix/MutexAttr.h>
#include <giglgu/posix/Mutex.h>

#include <pthread.h>	// PTHREAD_MUTEX_RECURSIVE
#include <signal.h>     // SIGALRM
#include <stdlib.h>     // EXIT_FAILURE
#include <unistd.h>	// alarm
#include <iostream>	// std::cout

using namespace giglgu::posix;

void on_SIGALRM(int)
{
  exit(EXIT_FAILURE); // abort with error code
}

int main(const int argc, const char** argv)
{
  signal(SIGALRM, on_SIGALRM);
  alarm(10); // set up a timeout

  MutexAttr attr;
  attr.setType(PTHREAD_MUTEX_RECURSIVE);
  attr.setRobust(PTHREAD_MUTEX_ROBUST);
  Mutex mutex(attr);
  mutex.lock();
    mutex.lock();
      std::cout << "Succesfully locked recursive mutex twice.\n";
    mutex.unlock();
  mutex.unlock();

  alarm(0); // cancel timeout
  return EXIT_SUCCESS;
}
