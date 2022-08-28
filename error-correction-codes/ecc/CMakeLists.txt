add_library(RepetitionCode
	repetition31/repetition_encode.c
	repetition31/repetition_decode.c
)
target_link_libraries(RepetitionCode PUBLIC BitArray)
target_include_directories(RepetitionCode INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/repetition31)

add_library(HammingCode
	hamming84/hamming_encode.c
	hamming84/hamming_decode.c
	hamming84/hamming_impl.c
)
target_link_libraries(HammingCode PUBLIC BitArray)
target_include_directories(HammingCode INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/hamming84)

add_library(Interleaver
	interleaver/interleaver_free.c
	interleaver/interleaver_init.c
	interleaver/interleaver_process_data.c
	interleaver/interleaver_impl.c
)
target_link_libraries(Interleaver PUBLIC BitArray)
target_include_directories(Interleaver INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/interleaver)
