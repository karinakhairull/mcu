cmake_minimum_required(VERSION 3.15)

# Указываем плату и микроконтроллер
set(PICO_BOARD pico)
set(PICO_PLATFORM rp2040)

# Подключаем Pico SDK
include(pico_sdk_import.cmake)

# Название проекта
project(02_echo)

# Инициализация SDK
pico_sdk_init()

# Добавляем исполняемый файл
add_executable(${PROJECT_NAME}
    main.c
)

# Подключаем библиотеки
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
)

# Настройка вывода через USB (важно для терминала!)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_enable_stdio_usb(${PROJECT_NAME} 1)

# Генерируем .uf2 файл
pico_add_extra_outputs(${PROJECT_NAME})