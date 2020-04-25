cmake_minimum_required(VERSION 3.10)
project(IpcQueuesV2)
add_executable(server server.c help.c)
add_executable(client client.c help.c)
