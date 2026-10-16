add_library(my_functions STATIC average.cpp average_random.cpp)

target_include_directories(my_functions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
