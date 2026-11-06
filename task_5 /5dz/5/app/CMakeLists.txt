# The application module defines the executable and its dependency.
add_executable(program main.cpp)
target_link_libraries(program PRIVATE my_functions)
