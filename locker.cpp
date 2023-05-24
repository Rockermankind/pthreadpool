#include "locker.h"
#include <exception>
#include <pthread.h>
#include <semaphore.h>

locker::locker()
    : m_mutex(PTHREAD_MUTEX_INITIALIZER), m_cond(PTHREAD_COND_INITIALIZER) {}
locker::~locker() {}

void locker::Lock() {
  if (pthread_mutex_lock(&m_mutex) != 0) {
    throw std::exception();
  }
}

void locker::Unlock() {
  if (pthread_mutex_unlock(&m_mutex)) {
    throw std::exception();
  }
}
sem::sem() {
  if (sem_init(&m_sem, 0, 0) != 0) {
    throw std::exception();
  }
}
sem::~sem() { sem_destroy(&m_sem); }

void sem::Wait() {
  if (sem_wait(&m_sem) != 0) {
    throw std::exception();
  }
}

void sem::Post() {
  if (sem_post(&m_sem) != 0) {
    throw std::exception();
  }
}

void locker::notify_all() {
  if (pthread_cond_broadcast(&m_cond) != 0) {
    throw std::exception();
  }
}

void locker::notify_one() {
  if (pthread_cond_signal(&m_cond) != 0) {
    throw std::exception();
  }
}

void locker::wait() {
  if (pthread_cond_wait(&m_cond, &m_mutex) != 0) {
    throw std::exception();
  }
}
