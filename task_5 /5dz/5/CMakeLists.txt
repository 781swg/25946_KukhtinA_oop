cmake_minimum_required(VERSION 3.14)
project(OOP_05 LANGUAGES CXX)

# стандарт c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# подключаем библиотеку
add_subdirectory(my_lib)

# создаем программу
add_executable(program main.cpp)
target_link_libraries(program PRIVATE my_functions)

# переключатель тестов
option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()