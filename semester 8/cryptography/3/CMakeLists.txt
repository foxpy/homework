cmake_minimum_required(VERSION 3.1)
project("GOST" LANGUAGES C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(demo demo.c gost_key.c gost_init.c util.c gost_encrypt.c gost_decrypt.c)
target_link_libraries(demo PUBLIC m)
