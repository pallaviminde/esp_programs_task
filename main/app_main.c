#include "app_main.h"
#include "config.h"

/*void app_main(void)
{
    //gpio_led_blink(LED_PIN1); //led blink example
    //gpio_led_polling(LED_PIN1); //led polling example
    //gpio_button_polling(LED_PIN1, BUTTON_PIN); //button polling example
}*/

/*// uart task code
void led_init(void);

void app_main(void)
{
   uart_init(); 
   led_init();
   
   xTaskCreate(receive_string, "uart_rx_task", 4095, NULL, 5, NULL);

    while(1)
    {
        ESP_LOGI("APP_MAIN_TAG","APP_MAIN");
        vTaskDelay(pdMS_TO_TICKS(1000));
    } 
}*/


/*
//task creation
void app_main(void)
{
    xTaskCreate(led_task1, "led_task", 2048, NULL, 5, NULL);
    vTaskDelay(pdMS_TO_TICKS(1000));
    xTaskCreate(led_task2, "led_task2", 2048, NULL,3, NULL);
    vTaskDelay(pdMS_TO_TICKS(1000));
}
*/


/* led task createt example
//task creation whith parameter passing

void app_main(void)
{
    gpio_num_t led1 = LED_PIN1;
    gpio_num_t led2 = LED_PIN2;

    xTaskCreate(led_task_with_param, "LED1",2048, (void*) led1, 5, NULL);
    vTaskDelay(pdMS_TO_TICKS(1000));
    xTaskCreate(led_task_with_param, "LED2",2048, (void*) led2, 4, NULL); 
    vTaskDelay(pdMS_TO_TICKS(1000));
}
*/


/* //queue example
void app_main(void)
{
    rtos_tasks_init();
}*/


 /*//semaphore example
void app_main(void)
{
    xSemaphore = xSemaphoreCreateBinary(); // binary create

    xTaskCreate(give_task, "Give Task", 2048, NULL, 1, NULL);
    xTaskCreate(take_task, "Take Task", 2048, NULL, 1, NULL);

}*/


/*//button semaphore task
void app_main(void)
{
    // Create binary semaphore
    buttonSemaphore = xSemaphoreCreateBinary();

    if (buttonSemaphore == NULL)
    {
        printf("Failed to create semaphore!\n");
        return;
    }

    // Create tasks
    xTaskCreate(button_task, "Button Task", 4096, NULL, 2, NULL);
    xTaskCreate(work_task, "Work Task", 4096, NULL, 1, NULL);
}*/


/*// mutex example

void app_main(void)
{
    counterMutex = xSemaphoreCreateMutex();

    xTaskCreate(mutex_task1, "Task1", 2048, NULL, 2, NULL);
    xTaskCreate(mutex_task2, "Task2", 2048, NULL, 2, NULL);
}*/


/*//led_mutex_example
void app_main(void)
{
    gpio_set_direction(LED_PIN1, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN1, 0);  // Start with LED OFF

    ledMutex = xSemaphoreCreateMutex();

    if (ledMutex == NULL)
    {
        printf("Mutex creation failed!\n");
        while(1) { vTaskDelay(pdMS_TO_TICKS(1000)); }  // Halt here
    }
    else
    {
        printf("Mutex created successfully\n");
    }

    xTaskCreate(mutex_button_task, "Button Task", 2048, NULL, 2, NULL);
    xTaskCreate(mutex_blink_task, "Blink Task", 2048, NULL, 1, NULL);
}*/

/*watchdog example
void app_main(void)
{
    esp_task_wdt_config_t wdt_config = {
        .timeout_ms = 5000,  // 5 seconds
        .idle_core_mask = (1 << CONFIG_FREERTOS_NUMBER_OF_CORES) - 1,
        .trigger_panic = true
    };

    // Initialize watchdog
    esp_task_wdt_init(&wdt_config);
    esp_task_wdt_add(NULL);  // Add main task to watchdog

    // Create tasks
    xTaskCreate(normal_task, "Normal Task", 2048, NULL, 5, NULL);
    xTaskCreate(stuck_task, "Stuck Task", 2048, NULL, 5, NULL);
}
*/

//wifi connectivity example
void app_main(void)
{
    //wifi_station_mode_example(); //wifi station mode example
    wifi_event_example(); //wifi event example
   //wifi_reconnect_example(); //wifi reconnect example
    //wifi_network_monitor(); //wifi network monitor example
    //wifi_init(); //tcp client example
    //tcp_client_test();
}