#ifndef RTOS_TASK_H            // Prevents multiple inclusion of this header file
#define RTOS_TASK_H
#include <stdio.h>            // Standard I/O functions (e.g., printf)
#include "freertos/FreeRTOS.h" // FreeRTOS core functions and types
#include "freertos/task.h"     // FreeRTOS task management functions
#include "freertos/queue.h"    // FreeRTOS queue functions and types
#include "freertos/semphr.h"   // FreeRTOS semaphore functions and types
#include "esp_task_wdt.h"     // ESP-IDF watchdog timer functions
#include "driver/gpio.h"      // GPIO driver functions and types
#include "gpio_driver.h"     // GPIO control functions

/*// watchdog example  Demonstrates how watchdog behaves when a task gets stuck
void normal_task(void *arg); 
void stuck_task(void *arg);*/



/*extern SemaphoreHandle_t ledMutex; // led mutex example , Protects shared resource (LED) using mutex

void mutex_button_task(void *arg);
void mutex_blink_task(void *arg); */


/* extern SemaphoreHandle_t counterMutex; // Mutex example , Prevents race condition on shared counter variable

void mutex_task1(void *arg);
void mutex_task2(void *arg);*/

/*extern SemaphoreHandle_t buttonSemaphore; // semaphore button example , Button gives semaphore → worker task executes
void button_task(void*arg);
void work_task(void*arg);*/

extern SemaphoreHandle_t xSemaphore; // semaphore simple example
void give_task(void*arg);
void take_task(void*arg);

// void rtos_tasks_init(void);  //for queue example

#endif