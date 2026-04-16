#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "sdkconfig.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"
#include "config.h"


#define LED_PIN1   GPIO_NUM_4
#define LED_PIN2   GPIO_NUM_5
#define BUTTON_PIN GPIO_NUM_37

void gpio_led_blink(gpio_num_t led);
void gpio_led_polling(gpio_num_t led);
void gpio_button_polling(gpio_num_t led, gpio_num_t button);
void gpio_button_interrupt_init(gpio_num_t led, gpio_num_t button);
void led_task1(void *pvParameters);
void led_task2(void *pvParameters);
void led_task_with_param(void *pvParameters);
#endif