add_library(work5 SHARED 5.c)
target_include_directories(work5 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(work15 SHARED 15.cpp)
target_include_directories(work15 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(work4 SHARED 4.cpp)
target_include_directories(work4 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
