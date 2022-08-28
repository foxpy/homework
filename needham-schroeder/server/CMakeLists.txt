add_executable(gen-schema gen-schema-header.c)
target_link_libraries(gen-schema PUBLIC qc)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/schema.h
    COMMAND gen-schema ${CMAKE_CURRENT_SOURCE_DIR}/schema.sql ${CMAKE_CURRENT_BINARY_DIR}/schema.h
    DEPENDS gen-schema schema.sql
)

add_executable(ns-server
    main.c
    server.c
    listen.c
    ${CMAKE_CURRENT_BINARY_DIR}/schema.h
)
target_include_directories(ns-server PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(ns-server PUBLIC qc SQLite::SQLite3 MqSetup CipherSuites)
