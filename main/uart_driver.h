#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <stdint.h>
#include <stdio.h>
#include<string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "config.h"
#include "gpio_driver.h"

#define UART_PORT UART_NUM_1
#define UART_TX_PIN 43
#define UART_RX_PIN 44
#define UART_BAUD_RATE 115200

void led_init(void);
void uart_init(void);
void transmit_string(const char *data);
void receive_string(void *arg);



#endif
