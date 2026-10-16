# A regular compiled static library: task 5.I-5.IV.
add_library(my_functions STATIC average.cpp average_random.cpp)

# PUBLIC makes the header folder visible to program and tests.
target_include_directories(my_functions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
