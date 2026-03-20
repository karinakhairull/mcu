#include <stdio.h>
#include "pico/stdlib.h"

#define DEVICE_NAME "my-pico-device"
#define DEVICE_VERSION "v1.0.0"

const uint LED_PIN = 25;

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);

    while (1) {
        char symbol = getchar();//getchar получает символы с клавиатуры
        printf("received char: %c [ ASCII code: %d ]\n", symbol, symbol);// выводит стандартное сообщение
        switch(symbol){ //switch проверяет какой это символ
        case 'e':
            gpio_put(LED_PIN, 1);
            printf("led enable done\n");
            break;
        case 'd':
            gpio_put(LED_PIN, 0);
            printf("led disable done\n");
            break;
        case 'v':
            printf("Device: %s, Version: %s\n", DEVICE_NAME, DEVICE_VERSION);
            break;
default: // любая другая клавиша - ничего не делаем
	break;}

    }
}
