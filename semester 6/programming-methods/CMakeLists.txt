cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(Hospital)

option(DEBUG_INFO "Print debug information to stderr" ON)
configure_file(config.h.in config.h)
add_executable(hospital
               main.cpp
               hospital.cpp
               human.cpp
               doctor.cpp
               patient.cpp
               disease.cpp)
target_include_directories(hospital PUBLIC "${PROJECT_BINARY_DIR}")
