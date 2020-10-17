add_library(Work4 SHARED 4.cpp)
target_include_directories(Work4 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Work5 SHARED 5.c)
target_link_libraries(Work5 PUBLIC qc)
target_include_directories(Work5 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Work15 SHARED 15.cpp)
target_include_directories(Work15 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Work18 SHARED 18.cpp)
target_include_directories(Work18 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
