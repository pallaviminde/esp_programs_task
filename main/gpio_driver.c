#include "config.h"
#include "gpio_driver.h"

// Global variable to track LED state (used in interrupt)
static bool led_state = false;

/* ---------- LED BLINK ---------- */
// This function blinks an LED connected to the specified GPIO pin using delay-based toggling.
void gpio_led_blink(gpio_num_t led) 
{
    gpio_set_direction(led, GPIO_MODE_OUTPUT); // Configure GPIO pin as output
    
    
    while (1)
    {
        gpio_set_level(led, 1);   // Turn LED ON
        esp_rom_delay_us(500000); // Delay for 500 milliseconds
        printf("LED_ON\n");       // Log LED state

        gpio_set_level(led, 0);   // Turn LED OFF
        esp_rom_delay_us(500000); // Delay for 500 milliseconds
        printf("LED_OFF\n");      // Log LED state
    }
}

/* ---------- LED POLLING ---------- */
// This function blinks an LED using FreeRTOS delay for non-blocking behavior.
void gpio_led_polling(gpio_num_t led) 
{
    gpio_set_direction(led, GPIO_MODE_OUTPUT); // Configure GPIO pin as output

    while (1)
    {
        gpio_set_level(led, 1);         // Turn LED ON
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 milliseconds (non-blocking)
        gpio_set_level(led, 0);        // Turn LED OFF
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 milliseconds (non-blocking)
    }
}

/* ---------- PUSH BUTTON POLLING 
 * Logic:
 * - Button pressed (0) → LED ON
 * - Button released (1) → LED OFF
 */
void gpio_button_polling(gpio_num_t led, gpio_num_t button)
{
    // Configure LED
    gpio_reset_pin(led);
    gpio_set_direction(led, GPIO_MODE_OUTPUT);

     // Configure Button (input with pull-up)
    gpio_reset_pin(button);
    gpio_set_direction(button, GPIO_MODE_INPUT);
    gpio_pullup_en(button);

    while (1)
    {
        int button_state = gpio_get_level(button);

        if (button_state == 0)       // Button pressed (active low)
            gpio_set_level(led, 1);
        else
            gpio_set_level(led, 0);      // Button released
        vTaskDelay(pdMS_TO_TICKS(500));  // Poll every 500 milliseconds


    }
}

/* ---------- ISR HANDLER ---------- */
static gpio_num_t isr_led_pin;
static void IRAM_ATTR button_isr_handler(void* arg)
{
    led_state = !led_state;                  // Toggle LED state on button press
    gpio_set_level(isr_led_pin, led_state);  // Update LED state
}

/* ---------- INTERRUPT INIT ---------- */
/*
 * Function: gpio_button_interrupt_init
 * -------------------------------------
 * Initializes button interrupt and LED control.
 *
 * Trigger:
 * - Negative edge (button press)
 */
void gpio_button_interrupt_init(gpio_num_t led_pin, gpio_num_t button_pin)
{

    // Configure LED
    gpio_reset_pin(led_pin);
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);
    isr_led_pin = led_pin;

    // Configure Button (input with pull-up and interrupt)
    gpio_reset_pin(button_pin);
    gpio_set_direction(button_pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(button_pin, GPIO_PULLUP_ONLY);

    // Set interrupt type to trigger on falling edge (button press)
    gpio_set_intr_type(button_pin, GPIO_INTR_NEGEDGE);

    // Install ISR service and add handler for button pin
    gpio_install_isr_service(0);
    gpio_isr_handler_add(button_pin, button_isr_handler, NULL);
}

/*LED TASK create without parameter*/

void led_task1(void *pvParameters)
{
    //gpio_num_t led = (gpio_num_t) pvParameters;
    gpio_set_direction(LED_PIN1, GPIO_MODE_OUTPUT);
   
    while(1)
    {
        gpio_set_level(LED_PIN1,1);
        vTaskDelay(pdMS_TO_TICKS(500));
        
        gpio_set_level(LED_PIN1,0);
        vTaskDelay(pdMS_TO_TICKS(500));
        
    }
    
}

void led_task2(void*pvParameters)
{
    gpio_set_direction(LED_PIN2, GPIO_MODE_OUTPUT);
   
    while(1)
    {
        gpio_set_level(LED_PIN2,1);
        vTaskDelay(pdMS_TO_TICKS(500));
        
        gpio_set_level(LED_PIN2,0);
        vTaskDelay(pdMS_TO_TICKS(500));
        
    }
        
}

/*led Taskcreate with parameter*/
void led_task_with_param(void *pvParameters)
{
    gpio_num_t led = (gpio_num_t) pvParameters;
    gpio_set_direction(led, GPIO_MODE_OUTPUT);
   
    while(1)
    {
        gpio_set_level(led,1);
        vTaskDelay(pdMS_TO_TICKS(500));
        
        gpio_set_level(led,0);
        vTaskDelay(pdMS_TO_TICKS(500));
        
    }
        
}