add_library(RandomGenerator rnd_init.c rndNN.c)
target_include_directories(RandomGenerator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
