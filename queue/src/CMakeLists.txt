add_library(
    queue
    SHARED
    queue.c
)

target_include_directories(
    queue
    PUBLIC
    ../include
)