# This file is used only when BUILD_TESTS=ON.
add_executable(average_tests test_average.cpp)

# The tests use our functions and Google's test framework.
target_link_libraries(average_tests PRIVATE my_functions GTest::gtest_main)

# Allow ctest to discover individual Google Test cases.
include(GoogleTest)
gtest_discover_tests(average_tests)
