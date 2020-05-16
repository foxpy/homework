add_library(ErrorCorrectionCodes
	repetition_encode.c
	repetition_decode.c
	hamming_encode.c
	hamming_decode.c
)
target_link_libraries(ErrorCorrectionCodes PUBLIC BitArray)
target_include_directories(ErrorCorrectionCodes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
