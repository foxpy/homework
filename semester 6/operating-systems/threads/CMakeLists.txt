cmake_minimum_required(VERSION 3.10)
project(Threads)

option(SYN_MUTEX "Use pthread mutexes as a synchronisation primitive" OFF)
option(SYN_SEMA "Use pthread semaphores as a synchronisation primitive" OFF)
option(SYN_ATOM "Use atomics as a synchronisation primitive" OFF)
configure_file(config.h.in config.h)

add_executable(threads threads.c writer.c reader.c crc.c)
target_include_directories(threads PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(threads pthread)
