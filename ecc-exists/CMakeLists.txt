cmake_minimum_required(VERSION 3.1)
project(EccExists)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
if(NOT MSVC)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()
if(NOT WIN32)
    link_libraries(m)
endif()

add_subdirectory(qc)

add_executable(ecc-exists
    ecc-exists.c
    singleton_bound.c
    hamming_bound.c
    gilbert_bound.c
    gilbert_varshamov_bound.c
    util.c
)
target_link_libraries(ecc-exists PUBLIC qc)
