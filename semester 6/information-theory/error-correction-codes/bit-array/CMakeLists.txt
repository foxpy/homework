add_library(BitArray
	bitarray_alloc.c
	bitarray_free.c
	bitarray_copy.c
	bitarray_size.c
	bitarray_empty.c
	bitarray_push_back.c
	bitarray_pop_back.c
	bitarray_back.c
	bitarray_front.c
	bitarray_push_front.c
	bitarray_pop_front.c
	bitarray_fill_from_memory.c
	bitarray_to_memory.c
)
target_include_directories(BitArray INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
