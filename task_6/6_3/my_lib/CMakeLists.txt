# статическая библиотека класса
add_library(robot STATIC robot.cpp)
target_include_directories(robot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
