add_library(NoiseSimulator noise.c)
target_include_directories(NoiseSimulator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
