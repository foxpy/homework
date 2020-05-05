set(RUNTIME_OUTPUT_DIRECTORY tests)

add_executable(noise-test noise-test.c)
target_link_libraries(noise-test PUBLIC NoiseSimulator)

add_executable(bit-test bit-test.c)
target_link_libraries(bit-test PUBLIC BitArray)

add_executable(cmdopts-test cmdopts-test.c)
target_link_libraries(cmdopts-test PUBLIC CmdOpts)
