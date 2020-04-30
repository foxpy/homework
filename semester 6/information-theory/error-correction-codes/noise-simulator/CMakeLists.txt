set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
add_library(NoiseSimulator noise.c)
target_include_directories(NoiseSimulator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
