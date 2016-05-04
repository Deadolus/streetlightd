/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

class Queue
{
public:
  typedef std::function<void()> T;

  void enqueue(T call);

  bool dequeue(T &call);

  void close();

private:
  bool finished{false};
  std::queue<T> queue{};

  std::mutex mutex{};
  std::condition_variable notEmpty{};

};

#endif
