# Требуем минимальную версию cmake
cmake_minimum_required(VERSION 3.15)

# Задаем параметры платы и микроконтроллера
set(PICO_BOARD pico)
set(PICO_PLATFORM rp2040)

# Подключаем Pico SDK
include(pico_sdk_import.cmake)

# Создаем проект
project(01_blink)

# Инициализируем SDK
pico_sdk_init()

# Добавляем исполняемый файл - ИСПРАВЛЕНО: убран слеш
add_executable(01_blink
    main.c
)

# Подключаем библиотеки
target_link_libraries(01_blink
    pico_stdlib
)

# Указываем скрипт компоновщика - ИСПРАВЛЕНО: убран слеш
pico_set_linker_script(01_blink memmap_rp2040.ld)

# Добавляем дополнительные выходные форматы
pico_add_extra_outputs(01_blink)
