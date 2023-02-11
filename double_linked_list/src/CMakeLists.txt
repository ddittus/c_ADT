add_library(
    d_list
    SHARED
    d_list.c
)

target_include_directories(
    d_list
    PUBLIC
    ../include
)