#include "rtos_task.h"

// Queue Handle
static QueueHandle_t data_queue;

// Producer Task
static void producer_task(void *pvParameters)
{
    int sensor_value = 0;

    while (1)
    {
        sensor_value++; // Simulate sensor reading (incrementing value)
        // Send the sensor value to the queue (blocks if queue is full)
        xQueueSend(data_queue, &sensor_value, portMAX_DELAY);
        printf("Sent: %d\n", sensor_value);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

// Consumer Task
// This task receives data from the queue and processes it (e.g., prints it).
static void consumer_task(void *pvParameters)
{
    int received_value;

    while (1)
    {
        // Wait indefinitely for data to be available in the queue and receive it
        if (xQueueReceive(data_queue, &received_value, portMAX_DELAY))
        {
            printf("Received: %d\n", received_value);
        }
    }
}

// Initialization function (called from app_main)
void rtos_tasks_init(void)
{
    // Create a queue capable of holding 5 integers
    data_queue = xQueueCreate(5, sizeof(int));

    if (data_queue == NULL)
    {
        printf("Queue creation failed!\n");
        return;
    }

    // Create producer and consumer tasks
    xTaskCreate(producer_task, "Producer", 2048, NULL, 1, NULL);
    xTaskCreate(consumer_task, "Consumer", 2048, NULL, 1, NULL);
}

// semaphore simple example
SemaphoreHandle_t xSemaphore;

void give_task(void*arg) //giving signal
{
    while(1)
    {
        // Give the semaphore to unblock the take_task
        xSemaphoreGive(xSemaphore);
        printf("Semaphore Given\n");
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void take_task(void*arg) // taking signal
{
    while(1)
    {
        // Wait indefinitely for the semaphore to be given by give_task
        if(xSemaphoreTake(xSemaphore, portMAX_DELAY))
        {
            printf("Semaphore Taken\n");
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}

// Semaphore button example 

SemaphoreHandle_t buttonSemaphore;

void button_task(void *arg)
{
    // Configure GPIO as input
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    
    // Enable internal pull-up resistor
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    int last_state = 1;

    while (1)
    {
        int current_state = gpio_get_level(BUTTON_PIN);

        // Detect falling edge (button press)
        if (current_state == 0 && last_state == 1)
        {
            xSemaphoreGive(buttonSemaphore);
            printf("Button Pressed\n");
        }

        last_state = current_state;

        // Smaller delay for better responsiveness
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void work_task(void *arg)
{
    gpio_set_direction(LED_PIN1, GPIO_MODE_OUTPUT);

    int led_state = 0;


    while (1)
    {
        // Wait indefinitely for semaphore
        if (xSemaphoreTake(buttonSemaphore, portMAX_DELAY))
        {
            led_state = !led_state;
            gpio_set_level(LED_PIN1, led_state);

            printf("LED Toggled\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}


//mutex example

SemaphoreHandle_t counterMutex;
int shared_counter = 0;

void mutex_task1(void *arg)
{
    while (1)
    {
        // Take the mutex before accessing the shared counter
        if (xSemaphoreTake(counterMutex, portMAX_DELAY))
        {
            // Increment the shared counter and print its value
            shared_counter++;
            printf("Task1 Counter: %d\n", shared_counter);
            xSemaphoreGive(counterMutex);
        }

        // Delay to allow other task to run and prevent starvation
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void mutex_task2(void *arg)
{
    while (1)
    {
        // Take the mutex before accessing the shared counter
        if (xSemaphoreTake(counterMutex, portMAX_DELAY))
        {
            // Increment the shared counter and print its value
            shared_counter++;
            printf("Task2 Counter: %d\n", shared_counter);
            xSemaphoreGive(counterMutex);
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// mutext example with led
SemaphoreHandle_t ledMutex = NULL;  // Define the mutex

void mutex_button_task(void *arg)
{
    // Configure GPIO for button input with pull-up
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    // Track last button state for edge detection
    int last_state = 1;

    while (1)
    {
        // Read current button state
        int current = gpio_get_level(BUTTON_PIN);

        // Detect falling edge (button press)
        if (current == 0 && last_state == 1)  // Button pressed
        {
            // Attempt to take the mutex before controlling the LED
            if (xSemaphoreTake(ledMutex, portMAX_DELAY))
            {
                // Turn LED ON on button press
                gpio_set_level(LED_PIN1, 1);  

                printf("Button task turned LED ON\n");

                xSemaphoreGive(ledMutex);
            }
        }

        last_state = current;
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void mutex_blink_task(void *arg)
{
    while (1)
    {
        // Attempt to take the mutex before controlling the LED
        if (xSemaphoreTake(ledMutex, portMAX_DELAY))
        {
            // Turn LED OFF every 1 second
            gpio_set_level(LED_PIN1, 0);

            printf("Blink task turned LED OFF\n");

            xSemaphoreGive(ledMutex);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// watchdog example
void normal_task(void *arg)
{
    // Register this task to watchdog
    esp_task_wdt_add(NULL);

    while (1)
    {
        printf("Normal task is running...\n");
        esp_task_wdt_reset();   // feed watchdog
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void stuck_task(void *arg)
{
    // Register this task to watchdog
    esp_task_wdt_add(NULL);

    printf("Stuck task started...\n");

    while (1)
    {
        // Intentionally NOT resetting watchdog
        // This will trigger watchdog

        vTaskDelay(pdMS_TO_TICKS(100)); // yield CPU (important)
    }
}