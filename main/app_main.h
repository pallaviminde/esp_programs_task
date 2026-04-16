#ifndef APP_MAIN_H
#define APP_MAIN_H


#include "gpio_driver.h"
#include "adc_driver.h"
#include "uart_driver.h"
#include "rtos_task.h"
#include "esp_task_wdt.h"
#include "wifi_manager.h"
#include "config.h"



void app_main(void);

#endif