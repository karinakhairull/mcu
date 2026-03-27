cmake_minimum_required(VERSION 3.15)

set(PICO_BOARD pico)
set(PICO_PLATFORM rp2040)

include(pico_sdk_import.cmake)

project(02_echo)

pico_sdk_init()

add_executable(02_echo
    main.c
)

target_link_libraries(02_echo
    pico_stdlib
)

# Копируем файл в папку сборки
configure_file(memmap_rp2040.ld memmap_rp2040.ld COPYONLY)

# Указываем путь к скопированному файлу 
pico_set_linker_script(02_echo memmap_rp2040.ld)

pico_add_extra_outputs(02_echo)
