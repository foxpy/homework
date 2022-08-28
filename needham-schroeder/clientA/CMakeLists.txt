add_executable(ns-client-a
    main.c
)
target_link_libraries(ns-client-a PUBLIC qc rt MqSetup CipherSuites)
