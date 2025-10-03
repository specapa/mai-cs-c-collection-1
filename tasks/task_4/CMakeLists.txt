add_library(task4_lib mathconst.c)
target_include_directories(task4_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task4 main.c)
target_link_libraries(task4 PRIVATE utils task4_lib m)

add_executable(task4_tests
    task4_tests.cpp
)

target_link_libraries(task4_tests
    PRIVATE
    gtest_main
    task4_lib
    utils
    m
)

target_include_directories(task4_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_dependencies(task4_tests task4)

enable_testing()
add_test(NAME task4IntegrationTests COMMAND task4_tests)