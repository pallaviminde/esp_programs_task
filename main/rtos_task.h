#ifndef RTOS_TASK_H
#define RTOS_TASK_H
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "esp_task_wdt.h"
#include "driver/gpio.h"
#include "gpio_driver.h"

/*// watchdog example
void normal_task(void *arg);
void stuck_task(void *arg);*/



/*extern SemaphoreHandle_t ledMutex; // led mutex example

void mutex_button_task(void *arg);
void mutex_blink_task(void *arg); */


/* extern SemaphoreHandle_t counterMutex; // Mutex example

void mutex_task1(void *arg);
void mutex_task2(void *arg);*/

/*extern SemaphoreHandle_t buttonSemaphore; // semaphore button example
void button_task(void*arg);
void work_task(void*arg);*/

extern SemaphoreHandle_t xSemaphore; // semaphore simple example
void give_task(void*arg);
void take_task(void*arg);

// void rtos_tasks_init(void);  for queue example

#endif