# ищем или скачиваем google test
find_package(GTest CONFIG QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

# создаем тестовую программу
add_executable(robot_tests test_robot.cpp)
target_link_libraries(robot_tests PRIVATE robot GTest::gtest_main)

# регистрируем тесты
include(GoogleTest)
gtest_discover_tests(robot_tests)
