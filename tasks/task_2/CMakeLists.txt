add_library(task2_lib prime_at_n.c)
target_include_directories(task2_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task2 main.c)
target_link_libraries(task2 PRIVATE utils task2_lib m)
