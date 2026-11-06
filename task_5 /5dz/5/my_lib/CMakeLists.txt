add_library(my_functions INTERFACE)
# Передаём программе путь к заголовкам библиотеки.
target_include_directories(my_functions INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
