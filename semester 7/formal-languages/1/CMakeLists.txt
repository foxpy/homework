add_executable(detect detect.cpp detecter.cpp)

if(FL_TESTS)
    add_executable(detecter-test test.cpp detecter.cpp)
    add_test(NAME detecter-test COMMAND detecter-test)
endif()
