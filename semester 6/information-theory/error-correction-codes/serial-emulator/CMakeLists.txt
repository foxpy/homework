add_library(SerialEmulator
	serial_encode.c
	serial_decode.c
	serial_packet_length.c
	serial_impl.c
)
target_link_libraries(SerialEmulator PUBLIC BitArray)
target_include_directories(SerialEmulator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
