#include "stdio-task.h"
#include <stdio.h>
#include "pico/stdlib.h"

#define COMMAND_BUF_LEN 128 // максимальная длина строки

char command[COMMAND_BUF_LEN] = {0}; // хранит накопленные символы
int command_buf_idx; // счетчик уже имеющихся символов

void stdio_task_init()
{
    command_buf_idx = 0; // Обнуление счетчика
}

char* stdio_task_handle()
{
    int symbol = getchar_timeout_us(0);
    if (symbol == PICO_ERROR_TIMEOUT)
    {
        return NULL;
    }

    putchar(symbol);

    if (symbol == '\r' || symbol == '\n')
    {
        command[command_buf_idx] = '\0';
        command_buf_idx = 0;

        printf("received string: '%s'\n", command);

        return command;
    }

    if (command_buf_idx >= COMMAND_BUF_LEN - 1) // если накоплено уже 127 символов
    {
        command_buf_idx = 0; // сбрасываем буфер
        return NULL;
    }

    command[command_buf_idx] = (char)symbol;
    command_buf_idx++;
    return NULL;
}
