// заголовочный файл модуля LED-TASK
// Этот файл описывает состояния светодиода и функции
#pragma once
#include <stdint.h> 

//возможные состояния светодиода
typedef enum
{
    LED_STATE_OFF = 0,   // выключен
    LED_STATE_ON = 1,    // включен
    LED_STATE_BLINK = 2, // мигает
} led_state_t;

void led_task_init();                    // инициализация
void led_task_handle();
void led_task_state_set(led_state_t state); // установить состояние
void led_task_set_blink_period_ms(uint32_t period_ms); 
// устанавливает период мигания в миллисекундах