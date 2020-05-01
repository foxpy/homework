add_library(NoiseSimulator noise.c)
target_link_libraries(NoiseSimulator PUBLIC RandomGenerator)
target_include_directories(NoiseSimulator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
