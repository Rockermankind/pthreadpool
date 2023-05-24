cmake_minimum_required(VERSION 3.10)
project(test)
add_library(thread pthread_pool.cpp locker.cpp)
add_executable(test test.cpp)
target_link_libraries(test PUBLIC thread)

