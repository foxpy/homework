add_library(DatabaseWrapper
    database_new.c
    database_open.c
    database_close.c
    database_register.c
    database_check_credentials.c
    database_get_users.c
    database_delete_user.c
    database_get_books.c
    database_delete_book.c
    database_add_book.c
    database_restore_book.c
    database-wrapper_impl/schema.c
    database-wrapper_impl/hash_password.c
    database-wrapper_impl/check_password.c
    database-wrapper_impl/get_user.c
    database-wrapper_impl/validate_username.c
)
target_link_libraries(DatabaseWrapper PUBLIC qc SQLite::SQLite3 unofficial-sodium::sodium)
target_include_directories(DatabaseWrapper INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
