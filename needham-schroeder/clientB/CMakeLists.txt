add_executable(ns-client-b
    main.c
    )
target_link_libraries(ns-client-b PUBLIC qc rt MqSetup CipherSuites)
