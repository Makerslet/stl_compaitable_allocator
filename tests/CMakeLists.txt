cmake_minimum_required(VERSION 3.2)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

add_executable(test_allocator   test_allocator.cpp)

# включаем 14 стандарт для наших целей
set_target_properties(test_allocator PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# подключим инклуды из основного каталога проекта
target_include_directories(test_allocator
    PRIVATE "${PROJECT_SOURCE_DIR}/src"
)

target_include_directories(test_allocator
    PRIVATE ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(test_allocator
    ${GTEST_BOTH_LIBRARIES}
    Threads::Threads
)

# максимально строгие настройки компилятора
if (MSVC)
    target_compile_options(test_allocator PRIVATE
        /W4
    )
else ()
    target_compile_options(test_allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

add_test(test_allocator test_allocator)
