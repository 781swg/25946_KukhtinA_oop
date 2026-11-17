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
