// реализация модуля ADC-TASK
#include "adc-task.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

const uint ADC_GPIO_PIN = 26;      // GPIO 26
const uint ADC_CHANNEL = 0;         // АЦП канал 0 соответствует GPIO 26
const uint TEMP_SENSOR_CHANNEL = 4; 
const float ADC_REF_VOLTAGE = 3.3;  // опорное напряжение 3.3 В
const uint ADC_RESOLUTION = 4095;   // 12 бит - максимум 4095

// инициализация АЦП
void adc_task_init()
{
    // периферийный модуль АЦП
    adc_init();
    
    // настраиваем GPIO 26 как вход для АЦП
    adc_gpio_init(ADC_GPIO_PIN);
}

// измеряем напряжение
float adc_task_read_voltage()
{
    adc_select_input(ADC_CHANNEL);     // канал АЦП (0 = GPIO 26)
    
    uint16_t raw_value = adc_read();     // измерение и чтение значения (0...4095)
    
    float voltage = (raw_value / (float)ADC_RESOLUTION) * ADC_REF_VOLTAGE;     // Преобразуем в напряжение
    
    return voltage;
}
//ИЗМЕРЕНИЕ ТЕМПЕРАТУРЫ
float adc_task_read_temperature()
{
    // Выбираем канал 4 (встроенный датчик температуры)
    adc_select_input(TEMP_SENSOR_CHANNEL);
    
    // Запускаем измерение и читаем значение (0...4095)
    uint16_t raw_value = adc_read();
    
    // Преобразуем в напряжение
    float voltage = (raw_value / (float)ADC_RESOLUTION) * ADC_REF_VOLTAGE;
    
    // Преобразуем напряжение в температуру (°C)
    float temperature = 27.0f - (voltage - 0.706f) / 0.001721f;
    
    return temperature;
}