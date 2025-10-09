add_library(task8_lib bases.c)
target_include_directories(task8_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task8 main.c)
target_link_libraries(task8 PRIVATE utils task8_lib m)

add_executable(task8_tests
    task8_tests.cpp
)

target_link_libraries(task8_tests
    PRIVATE
    gtest_main
    task8_lib
    utils
    m
)

target_include_directories(task8_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_dependencies(task8_tests task8)

enable_testing()
add_test(NAME task8IntegrationTests COMMAND task8_tests)