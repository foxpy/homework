add_library(BitArray
	bitarray_alloc.c
	bitarray_free.c
	bitarray_size.c
	bitarray_empty.c
	bitarray_push_back.c
)
target_include_directories(BitArray INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
