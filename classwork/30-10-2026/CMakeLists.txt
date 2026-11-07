cmake_minimum_required(VERSION 3.14)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

project(Classwork09 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(robot robot.cpp factory.cpp squad.cpp)
target_include_directories(robot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(program main.cpp)
target_link_libraries(program PRIVATE robot)

option(BUILD_TESTS "Build Google Test fixture tests" ON)
if(BUILD_TESTS)
    enable_testing()
    find_package(GTest CONFIG QUIET)
    if(NOT GTest_FOUND)
        include(FetchContent)
        FetchContent_Declare(googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        )
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()
    add_executable(robot_tests tests/test_robot.cpp)
    target_link_libraries(robot_tests PRIVATE robot GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(robot_tests)
endif()
