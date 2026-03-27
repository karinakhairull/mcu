//Заголовочный файл PROTOCOL-TASK


#pragma once
// Защита от двойного включения
//указатель на функцию (колбэк)
// void(*command_callback_t)(const char* args) — это указатель на функцию,
// которая принимает строку с аргументами и ничего не возвращает
typedef void(*command_callback_t)(const char* args);

typedef struct // typedef — создаём новое имя для типа
{
    const char* command_name;     // имя команды (например, "version")
    command_callback_t command_callback; // функция, которая выполнится
    const char* command_help;     // описание команды
} api_t;

// Инициализация - передаём массив команд
void protocol_task_init(api_t* device_api);

//передаём строку, полученную от stdio
void protocol_task_handle(char* command_string);