// реализация модуля LED-TASK

// 1. Инициализация светодиода
// 2. Неблокирующее управление (без sleep_ms)
// 3. Три состояния: OFF, ON, BLINK

#include "led-task.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "stdint.h"

// константы и переменные
const uint LED_PIN = 25;              // пин встроенного светодиода
uint LED_BLINK_PERIOD_US = 500000;    // период мигания 500 мс (500000 мкс)

uint64_t led_ts;                      // метка времени для мигания
led_state_t led_state;                // текущее состояние светодиода

void led_task_init()
{
    // Начинаем с выключенного светодиода
    led_state = LED_STATE_OFF;
    
    // Обнуляем метку времени
    led_ts = 0;
    
    // Настраиваем пин светодиода как выход
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // Начинаем с выключенным светодиодом
    gpio_put(LED_PIN, 0);
}

// обработчик (вызывается постоянно в мейне)
void led_task_handle()
{
    switch (led_state)
    {
        case LED_STATE_OFF:
            // Светодиод выключен
            gpio_put(LED_PIN, 0);
            break;
            
        case LED_STATE_ON:
            // Светодиод включен
            gpio_put(LED_PIN, 1);
            break;
            
        case LED_STATE_BLINK:
            // мигание
            if (time_us_64() > led_ts)
            {
                // Обновляем метку времени на следующий полупериод
                led_ts = time_us_64() + (LED_BLINK_PERIOD_US / 2);
                
                // Переключаем светодиод (если был включён — выключаем, и наоборот)
                bool current_state = gpio_get(LED_PIN);
                gpio_put(LED_PIN, !current_state);
            }
            break;
            
        default:
            break;
    }
}

// Функция установки состояния
void led_task_state_set(led_state_t state)
{
    led_state = state;
    
    // Если переключаемся в режим мигания — сбрасываем таймер
    if (state == LED_STATE_BLINK)
    {
        led_ts = time_us_64() + (LED_BLINK_PERIOD_US / 2);
        gpio_put(LED_PIN, 1);  // начинаем с включенного
    }
}
//установка периода мигания
void led_task_set_blink_period_ms(uint32_t period_ms)
{
    // период не должен быть 0
    if (period_ms == 0)
    {
        return;
    }
    
    // Переводим миллисекунды в микросекунды
    LED_BLINK_PERIOD_US = period_ms * 1000;
    
    // Если светодиод сейчас мигает — сбрасываем таймер, чтобы не сбился ритм
    if (led_state == LED_STATE_BLINK)
    {
        led_ts = time_us_64() + (LED_BLINK_PERIOD_US / 2);
    }
}
