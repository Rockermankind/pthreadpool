#pragma once
#include "locker.h"
#include <functional>
#include <pthread.h>
#include <queue>
#include <stdexcept>
#include <thread>

class threadPool {
public:
  threadPool(int _size = 8);
  ~threadPool();

  void addTask(std::function<void()> _cb);

private:
  static void *run(void *args);

private:
  locker m_lock;
  std::queue<std::function<void()>> tasks;
  pthread_t *t;
  int size;
  int tasks_size;
  std::function<void()> cb;
  bool stop;
};
