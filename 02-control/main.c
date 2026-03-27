#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "stdio-task/stdio-task.h"
#include "protocol-task/protocol-task.h"
#include "led-task/led-task.h"

#define DEVICE_NAME "my-pico-device"
#define DEVICE_VERSION "v1.0.0"

void version_callback(const char* args);
void led_on_callback(const char* args);
void led_off_callback(const char* args);
void led_blink_callback(const char* args);
void led_blink_set_period_ms_callback(const char* args);
void help_callback(const char* args);
void mem_callback(const char* args);
void wmem_callback(const char* args);

api_t device_api[] =
{
    {"version", version_callback, "get device name and firmware version"},
    {"on", led_on_callback, "turn LED on"},
    {"off", led_off_callback, "turn LED off"},
    {"blink", led_blink_callback, "make LED blink"},
    {"set_period", led_blink_set_period_ms_callback, "set blink period in ms"},
    {"help", help_callback, "show this help message"},
    {"mem", mem_callback, "read memory at address (hex), e.g., mem 20000000"},
    {"wmem", wmem_callback, "write memory at address (hex), e.g., wmem 20000000 12345678"},
    {NULL, NULL, NULL},
};

void version_callback(const char* args)
{
    printf("device name: '%s', firmware version: %s\n", DEVICE_NAME, DEVICE_VERSION);
}

void led_on_callback(const char* args)
{
    led_task_state_set(LED_STATE_ON);
    printf("LED turned ON\n");
}

void led_off_callback(const char* args)
{
    led_task_state_set(LED_STATE_OFF);
    printf("LED turned OFF\n");
}

void led_blink_callback(const char* args)
{
    led_task_state_set(LED_STATE_BLINK);
    printf("LED blinking started\n");
}

void led_blink_set_period_ms_callback(const char* args)
{
    uint32_t period_ms = 0;
    int result = sscanf(args, "%u", &period_ms);
    
    if (result != 1 || period_ms == 0)
    {
        printf("Error: invalid period. Usage: set_period <milliseconds>\n");
        return;
    }
    
    led_task_set_blink_period_ms(period_ms);
    printf("Blink period set to %u ms\n", period_ms);
}

void help_callback(const char* args)
{
    printf("\n=== Available commands ===\n");
    for (int i = 0; device_api[i].command_name != NULL; i++)
    {
        printf("  %-15s - %s\n", 
               device_api[i].command_name, 
               device_api[i].command_help);
    }
    printf("==========================\n");
}

void mem_callback(const char* args)
{
    uint32_t addr = 0;
    
    // Пытаемся прочитать адрес (в шестнадцатеричном формате)
    int result = sscanf(args, "%x", &addr);
    
    if (result != 1)
    {
        printf("Error: invalid address. Usage: mem <hex_address>\n");
        return;
    }
    
    // Читаем значение по адресу
    uint32_t value = *((volatile uint32_t*)addr);
    
    printf("Memory at 0x%08X: 0x%08X (%u)\n", addr, value, value);
}

void wmem_callback(const char* args)
{
    uint32_t addr = 0;
    uint32_t value = 0;
    
    // Пытаемся прочитать адрес и значение (оба в шестнадцатеричном формате)
    int result = sscanf(args, "%x %x", &addr, &value);
    
    if (result != 2)
    {
        printf("Error: invalid arguments. Usage: wmem <hex_address> <hex_value>\n");
        return;
    }
    
    // Записываем значение по адресу
    *((volatile uint32_t*)addr) = value;
    
    printf("Written 0x%08X to address 0x%08X\n", value, addr);
}

int main()
{
    stdio_init_all();
    stdio_task_init();
    protocol_task_init(device_api);
    led_task_init();

    printf("\nDevice ready! Type 'help' to see available commands.\n");

    while (1)
    {
        char* command_string = stdio_task_handle();
        if (command_string != NULL)
        {
            protocol_task_handle(command_string);
        }
        led_task_handle();
    }
}