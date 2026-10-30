cmake_minimum_required(VERSION 3.14)
project(OOP_06_6_I LANGUAGES CXX)

# стандарт c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# подключаем библиотеку
add_subdirectory(my_lib)

# собираем программу
add_executable(program main.cpp)
target_link_libraries(program PRIVATE robot)
