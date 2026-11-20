cmake_minimum_required(VERSION 3.14)
project(ATMSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(atm_simulator main.cpp account.cpp atm.cpp)

option(BUILD_ATM_MOCKUP "Build the static C++ window using SDL2" OFF)
if(BUILD_ATM_MOCKUP)
    find_package(SDL2 CONFIG REQUIRED)
    add_executable(atm_mockup atm_mockup.cpp)
    if(TARGET SDL2::SDL2main)
        target_link_libraries(atm_mockup PRIVATE SDL2::SDL2main)
    endif()
    target_link_libraries(atm_mockup PRIVATE SDL2::SDL2)
endif()

option(BUILD_TESTS "Build ATM tests with Google Test" OFF)
if(BUILD_TESTS)
    enable_testing()
    find_package(GTest CONFIG QUIET)
    if(NOT TARGET GTest::gtest_main)
        include(FetchContent)
        FetchContent_Declare(googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        )
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()
    add_executable(atm_tests tests/test_atm.cpp account.cpp atm.cpp)
    target_include_directories(atm_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(atm_tests PRIVATE GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(atm_tests)
endif()
