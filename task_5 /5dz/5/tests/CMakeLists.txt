# ищем установленный google test
find_package(GTest CONFIG QUIET)

if(NOT GTest_FOUND)
    # скачиваем google test
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    # настройка для windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

# создаем программу тестов
add_executable(average_tests test_average.cpp)

# подключаем библиотеки
target_link_libraries(
    average_tests PRIVATE my_functions GTest::gtest_main
)

# регистрируем тесты
include(GoogleTest)
gtest_discover_tests(average_tests)