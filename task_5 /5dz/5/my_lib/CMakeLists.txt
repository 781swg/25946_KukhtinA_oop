cmake_minimum_required(VERSION 3.14)
project(OOP_05 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(my_functions INTERFACE)
# Передаём программе путь к заголовкам библиотеки.
target_include_directories(my_functions INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
