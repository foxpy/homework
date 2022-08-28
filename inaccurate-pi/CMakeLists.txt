cmake_minimum_required(VERSION 3.10)
project(InaccuratePi)

if(MSVC)
    add_compile_options(/W3)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(NOT WIN32)
    link_libraries(m)
endif()

add_subdirectory(qc)
add_executable(inaccurate-pi inaccurate-pi.c needle.c)
target_link_libraries(inaccurate-pi PUBLIC qc)
