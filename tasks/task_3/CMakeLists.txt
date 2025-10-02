add_library(task3_lib args.c math_operations.c)
target_include_directories(task3_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task3 main.c)
target_link_libraries(task3 PRIVATE utils m task3_lib)

add_executable(task3_tests
    task3_tests.cpp
)

target_link_libraries(task3_tests
    PRIVATE
    gtest_main
    task3_lib
    utils
    m
)

target_include_directories(task3_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_dependencies(task3_tests task3)

enable_testing()
add_test(NAME Task3IntegrationTests COMMAND task3_tests)