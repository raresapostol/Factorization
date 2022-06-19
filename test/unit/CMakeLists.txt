cmake_minimum_required(VERSION 3.8)

set(This ExampleTests)

set(SOURCES
    test.c
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    Example
)

add_test(
    NAME ${This}
    COMMAND ${This}
)