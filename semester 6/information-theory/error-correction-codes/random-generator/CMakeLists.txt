set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
add_library(RandomGenerator random.c)
target_include_directories(RandomGenerator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
