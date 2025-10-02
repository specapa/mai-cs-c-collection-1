add_library(task1_lib argc.c math_operations.c)
target_include_directories(task1_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task1 main.c)
target_link_libraries(task1 PRIVATE utils task1_lib)
