#pragma once
#include <pthread.h>
#include <semaphore.h>

class locker {
  typedef pthread_mutex_t Mutex;
  typedef pthread_cond_t Cond;

public:
  locker();
  ~locker();

  void Lock();

  void Unlock();

  void notify_one();

  void notify_all();

  void wait();

private:
  Mutex m_mutex;
  Cond m_cond;
};

class sem {
public:
  sem();
  ~sem();

  void Wait();

  void Post();

private:
  sem_t m_sem;
};
