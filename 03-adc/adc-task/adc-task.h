//adc-task Отвечает за измерение напряжения на GPIO 26

#pragma once

// инициализация АЦП
void adc_task_init();

float adc_task_read_voltage(); // Измеряет напряжение и возвращает значение в вольтах
float adc_task_read_temperature();