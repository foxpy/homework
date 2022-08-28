add_library(CipherSuites xorshift.c chacha.c)
target_link_libraries(CipherSuites PUBLIC qc ChaCha20)
target_include_directories(CipherSuites PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
