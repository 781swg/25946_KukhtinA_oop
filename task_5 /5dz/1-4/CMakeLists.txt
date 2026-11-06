cmake_minimum_required(VERSION 3.14)
project(OOP_05 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The library module is required by both the application and the tests.
add_subdirectory(my_lib)

# The executable program is configured by its own module.
add_subdirectory(app)

# Google Test is an optional module.
option(BUILD_TESTS "Build tests using Google Test" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
