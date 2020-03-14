cmake_minimum_required(VERSION 3.10)
project(Threads)
add_executable(threads threads.c writer.c reader.c)
target_link_libraries(threads pthread)
