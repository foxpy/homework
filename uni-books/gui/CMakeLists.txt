add_executable(uni-books
    main.cpp
    login-widget.cpp
    main-window.cpp
    admin-panel.cpp
    user-panel.cpp
)
target_link_libraries(uni-books PUBLIC fltk DatabaseWrapper)
