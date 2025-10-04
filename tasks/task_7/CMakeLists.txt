add_library(task7_lib file_process.c)
target_include_directories(task7_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task7 main.c)
target_link_libraries(task7 PRIVATE utils task7_lib m)

add_executable(task7_tests
    task7_tests.cpp
)

target_link_libraries(task7_tests
    PRIVATE
    gtest_main
    task7_lib
    utils
    m
)

target_include_directories(task7_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_dependencies(task7_tests task7)

enable_testing()
add_test(NAME task7IntegrationTests COMMAND task7_tests)