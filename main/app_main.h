#ifndef APP_MAIN_H        // Prevents multiple inclusion of this header file
#define APP_MAIN_H
#include "gpio_driver.h"   // GPIO control functions
#include "adc_driver.h"    // ADC reading and processing functions
#include "uart_driver.h"   // UART communication functions
#include "rtos_task.h"     // FreeRTOS task management
#include "esp_task_wdt.h"  // Watchdog timer functions
#include "wifi_manager.h"  // WiFi connectivity management functions
#include "config.h"        // Project-specific configuration (e.g., GPIO pins, WiFi credentials)

/*
 * Function: app_main
 * Main entry point of the ESP-IDF application.
 * Responsibilities:
 * - Initialize all drivers (GPIO, ADC, UART, etc.)
 * - Start RTOS tasks
 * - Initialize communication modules (WiFi, MQTT, etc.)
 */
void app_main(void);

#endif