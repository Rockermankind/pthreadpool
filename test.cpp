#include "pthread_pool.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;
void printLocal() {
  cout << "hello: ";
  cout << "pid:" << pthread_self() << endl;
}

int main() {
  threadPool *threads = new threadPool();
  for (int i = 0; i < 10; i++) {
    threads->addTask(&printLocal);
  }
  sleep(10);
  return 0;
}
