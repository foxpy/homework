set(RUNTIME_OUTPUT_DIRECTORY tests)

add_executable(noise-test noise-test.c)
target_link_libraries(noise-test PUBLIC NoiseSimulator)

add_executable(bit-test bit-test.c)
target_link_libraries(bit-test PUBLIC BitArray)

add_executable(cmdopts-test cmdopts-test.c)
target_link_libraries(cmdopts-test PUBLIC CmdOpts)

add_executable(bytes-to-string-test bytes-to-string-test.c)
target_link_libraries(bytes-to-string-test PUBLIC BytesToString)

add_executable(random-generator-test random-generator-test.c)
target_link_libraries(random-generator-test PUBLIC RandomGenerator)

add_executable(serial-test serial-test.c)
target_link_libraries(serial-test PUBLIC SerialEmulator BitArray BytesToString)

add_executable(ecc-repetition-test ecc-repetition-test.c)
target_link_libraries(ecc-repetition-test PUBLIC ErrorCorrectionCodes)
