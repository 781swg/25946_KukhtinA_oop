cmake_minimum_required(VERSION 3.14)
project(OOP_05 LANGUAGES CXX)

# стандарт c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# подключаем библиотеку
add_subdirectory(my_lib)

# создаем программу и подключаем библиотеку
add_executable(program main.cpp)
target_link_libraries(program PRIVATE my_functions)

# включение и отключение тестов
option(BUILD_TESTS "Build tests using Google Test" OFF)

if(BUILD_TESTS)
    # ищем установленный google test
    find_package(GTest CONFIG QUIET)

    if(NOT GTest_FOUND)
        # скачиваем google test
        include(FetchContent)
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        )

        # настройка для windows
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()

    # включаем тестирование
    enable_testing()

    # подключаем папку с тестами
    add_subdirectory(tests)
endif()