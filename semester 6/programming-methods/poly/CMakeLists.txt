cmake_minimum_required(VERSION 3.10)
project(Hospital)
add_executable(hospital main.cpp
                        hospital.cpp
                        human.cpp
                        patient.cpp
                        doctor.cpp
                        disease.cpp)
