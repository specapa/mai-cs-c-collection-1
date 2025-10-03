add_library(task6_lib integral.c)
target_include_directories(task6_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task6 main.c)
target_link_libraries(task6 PRIVATE utils task6_lib m)

add_executable(task6_tests
    task6_tests.cpp
)

target_link_libraries(task6_tests
    PRIVATE
    gtest_main
    task6_lib
    utils
    m
)

target_include_directories(task6_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_dependencies(task6_tests task6)

enable_testing()
add_test(NAME task6IntegrationTests COMMAND task6_tests)