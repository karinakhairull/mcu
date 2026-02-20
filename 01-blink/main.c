#include "pico/stdlib.h"
#include "hardware/gpio.h"

const uint LED_PIN = 25;

int main()
{
    // Инициализация пина
    gpio_init(LED_PIN);
    
    // Настройка как выход
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // Бесконечный цикл
    while (1)
    {
        gpio_put(LED_PIN, 1);  // Включить светодиод
        sleep_ms(250);           // Подождать 250 мс
        gpio_put(LED_PIN, 0);  // Выключить светодиод
        sleep_ms(1000);          // Подождать 1000 мс
    }
}
