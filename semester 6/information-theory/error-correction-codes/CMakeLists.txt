cmake_minimum_required(VERSION 3.10)
project(ErrorCorrectionCodes)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_subdirectory(noise-simulator)
add_subdirectory(random-generator)
add_executable(noise-demo noise-demo.c)
target_link_libraries(noise-demo PUBLIC NoiseSimulator)
