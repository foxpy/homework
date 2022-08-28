add_library(MqSetup mq_setup.c)
target_link_libraries(MqSetup PUBLIC rt qc)
target_include_directories(MqSetup PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
