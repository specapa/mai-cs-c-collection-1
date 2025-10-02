add_library(task2_lib prime_at_n.c)
target_include_directories(task2_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task2 main.c)
target_link_libraries(task2 PRIVATE utils task2_lib m)

add_executable(task2_tests
    task2_tests.cpp
)

target_link_libraries(task2_tests
    PRIVATE
    gtest_main
    task3_lib
    utils
    m
)

target_include_directories(task2_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_dependencies(task2_tests task2)

enable_testing()
add_test(NAME Task2IntegrationTests COMMAND task2_tests)