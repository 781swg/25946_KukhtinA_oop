
find_package(GTest CONFIG QUIET)
if(NOT TARGET GTest::gtest_main)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(average_tests test_average.cpp) // тестовая программа
target_link_libraries(average_tests PRIVATE my_functions GTest::gtest_main)

# Register individual Google Test cases with CTest.
include(GoogleTest)
gtest_discover_tests(average_tests)
