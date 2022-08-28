add_library(RandomGenerator
	rnd_init.c
	rndNN.c
	rnd_fpNN.c
	normal_distribution.c
	random_impl.c
)
target_include_directories(RandomGenerator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
