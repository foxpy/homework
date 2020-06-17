add_library(NoiseSimulator
	noise_init_bit_flip.c
	noise_init_temporal.c
	noise_init_burst.c
	noise_free.c
	noise_apply.c
)
target_link_libraries(NoiseSimulator PUBLIC
	RandomGenerator
	BitArray
)
target_include_directories(NoiseSimulator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
