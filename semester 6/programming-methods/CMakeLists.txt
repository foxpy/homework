cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Hospital)
add_executable(hospital
               main.cpp
               hospital.cpp
               human.cpp
               doctor.cpp
               patient.cpp
               disease.cpp)
