cmake_minimum_required(VERSION 3.1)
project(FormalLanguages)

option(FL_TESTS "Build tests" OFF)
if(FL_TESTS)
    enable_testing()
endif()

add_subdirectory(1)
