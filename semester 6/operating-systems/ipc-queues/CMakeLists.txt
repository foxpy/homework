cmake_minimum_required(VERSION 3.10)

project(IPC)
add_executable(ipc-queues ipc-queues.c)
target_link_libraries(ipc-queues rt)
