cmake_minimum_required(VERSION 3.2)

# устанавливаем имя проекта и его версию
if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    message("TRAVIS_BUILD_NUMBER IS DEFINED:" $ENV{TRAVIS_BUILD_NUMBER})
    project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    message("TRAVIS_BUILD_NUMBER IS NOT DEFINED")
    project(allocator VERSION 0.0.1)
endif()

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

# включаем тесты
enable_testing()

# подключаем тесты
add_subdirectory(src)
add_subdirectory(tests)
