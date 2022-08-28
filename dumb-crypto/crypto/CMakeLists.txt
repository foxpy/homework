add_library(Crypto
    caesar.c
    affine_caesar.c
    encryption_table.c
    encryption_table_single_permutation.c
    encryption_table_double_permutation.c
    magic_square.c
    caesar_keyword.c
    trithemius.c
    playfair.c
    vigenere.c
    wheatstone_two_square.c
    polybius_square.c
    polybius-square-v2.c
    proportional-permutation.c
)
target_link_libraries(Crypto PUBLIC Unicode String)
target_include_directories(Crypto INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
