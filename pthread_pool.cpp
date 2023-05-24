#include "pthread_pool.h"
#include <functional>
#include <stdexcept>
#include <thread>
// 初始化时创建多个线程，绑定静态函数和对象
threadPool::threadPool(int _size)
    : size(_size), stop(false), m_lock(), tasks_size(0) {
  if (size <= 0) {
    throw std::logic_error("wrong size number");
  }
  t = new pthread_t[size];
  for (int i = 0; i < size; i++) {
    if (pthread_create(t, NULL, run, this) != 0) {
      throw std::runtime_error("pthread create error");
    }
  }
}
// 析构时等待线程工作完成
threadPool::~threadPool() {
  m_lock.Lock();
  stop = true;
  m_lock.Unlock();
  m_lock.notify_all();
  for (int i = 0; i < size; i++) {
    if (pthread_join(t[i], NULL) != 0) {
      pthread_exit(NULL);
    }
  }
  delete[] t;
}
// 将函数对象装入任务队列
void threadPool::addTask(std::function<void()> _cb) {
  m_lock.Lock();
  tasks.push(_cb);
  m_lock.Unlock();
  m_lock.notify_one();
}
// 静态函数动态调用类中的function函数对象
void *threadPool::run(void *args) {
  threadPool *threads = static_cast<threadPool *>(args);
  while (!threads->stop) {
    threads->m_lock.Lock();
    while (threads->tasks.empty() && !threads->stop) {
      threads->m_lock.wait();
    }
    threads->cb = threads->tasks.front();
    threads->tasks
        .pop(); // 取任务队列中对象后弹出,并赋给运行时对象(threads)的函数对象function
    threads->m_lock.Unlock();
    threads->m_lock.Lock();
    threads->cb();
    threads->m_lock.Unlock();
  }
  return NULL;
}
