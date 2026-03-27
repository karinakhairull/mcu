// Реализация модуля PROTOCOL-TASK
// 1. Хранение списка команд
// 2. Разбор входящей строки на "команда" и "аргументы"
// 3. Поиск команды и вызов её колбэка

// подключаем заголовки
#include "protocol-task.h"  // наш заголовок
#include <stdio.h>          // для printf
#include <string.h>         // для strcmp, strchr

// глобальные переменные модуля static = видны только в этом файле
static api_t* api = {0};        // указатель на массив команд
static int commands_count = 0;  // количество команд в массиве

// ФУНКЦИЯ ИНИЦИАЛИЗАЦИИ
void protocol_task_init(api_t* device_api)
{
    api = device_api; // сохраняем указатель на массив команд
    
    // Подсчитываем количество команд
    // Идём по массиву, пока не встретим элемент с command_name == NULL
    commands_count = 0;
    while (api[commands_count].command_name != NULL)
    {
        commands_count++;
    }
    // Теперь commands_count = сколько команд в массиве
}

// ФУНКЦИЯ-ОБРАБОТЧИК
void protocol_task_handle(char* command_string)
{
    // 1. проверка на наличие строки
    if (command_string == NULL)
    {
        // Нет строки — выходим
        return;
    }
    
    // 2. разбираем строку на "команда" и "аргументы"
    
    const char* command_name = command_string;     // начало строки
    const char* command_args = NULL;               // аргументы 
    
    // Ищем первый пробел в строке
    char* space_symbol = strchr(command_string, ' ');
    
    if (space_symbol != NULL)
    {
        // Нашли пробел
        *space_symbol = '\0';              // Заменяем пробел на ноль (разделяем строку)
        command_args = space_symbol + 1;   // Аргументы — после пробела
    }
    else
    {
        // Пробела нет — аргументов нет
        command_args = "";
    }
    
    printf("DEBUG: command='%s', args='%s'\n", command_name, command_args);
    
    // 3. поиск команды в списке
    for (int i = 0; i < commands_count; i++)
    {
        // Сравниваем имя команды с тем, что в массиве
        if (strcmp(command_name, api[i].command_name) == 0)
        {
            // Вызываем колбэк, передаём аргументы
            api[i].command_callback(command_args);
            return;
        }
    }
    // 4. команда не найдена, поэтому выводим ошибку
    printf("Error: unknown command '%s'\n", command_name);
}