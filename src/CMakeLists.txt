cmake_minimum_required(VERSION 3.2)


add_executable(allocator main.cpp custom_forward_list.h allocator.h)

# включаем 14 стандарт для наших целей
set_target_properties(allocator PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# максимально строгие настройки компилятора
if (MSVC)
    target_compile_options(allocator PRIVATE
        /W4
    )
    target_compile_options(allocator PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

# бинарник кладем в каталог bin
install(TARGETS allocator RUNTIME DESTINATION bin)

# генерить будем deb пакет
set(CPACK_GENERATOR DEB)

# конфигурируем deb пакет
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_CONTACT oshuev.valery@yandex.ru)

# подключем генератор пакетов
include(CPack)
