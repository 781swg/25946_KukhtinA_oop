cmake_minimum_required(VERSION 3.14)
project(OOP_05 LANGUAGES CXX)

# Using the C++17 language standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build the library in the my_lib subfolder.
add_subdirectory(my_lib)

# Create the main program and link our library.
add_executable(program main.cpp)
target_link_libraries(program PRIVATE my_functions)

# Task 5.IV: build Google Tests only if requested.
option(BUILD_TESTS "Build tests using Google Test" OFF)

if(BUILD_TESTS)
    # Prefer an already installed Google Test library.
    find_package(GTest CONFIG QUIET)

    if(NOT GTest_FOUND)
        # Otherwise download Google Test during CMake configuration.
        include(FetchContent)
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        )
        # Windows setting: do not override the parent project's runtime settings.
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()

    enable_testing()
    add_subdirectory(tests)
endif()
