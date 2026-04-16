#include "config.h"
#include "gpio_driver.h"

static bool led_state = false;

/* ---------- LED BLINK ---------- */
void gpio_led_blink(gpio_num_t led)
{
    gpio_set_direction(led, GPIO_MODE_OUTPUT);
    
    
    while (1)
    {
        gpio_set_level(led, 1);
        esp_rom_delay_us(500000);
        printf("LED_ON\n");

        gpio_set_level(led, 0);
        esp_rom_delay_us(500000);
        printf("LED_OFF\n");
    }
}

/* ---------- LED POLLING ---------- */
void gpio_led_polling(gpio_num_t led)
{
    gpio_set_direction(led, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(led, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(led, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

/* ---------- PUSH BUTTON POLLING ---------- */
void gpio_button_polling(gpio_num_t led, gpio_num_t button)
{
    gpio_reset_pin(led);
    gpio_set_direction(led, GPIO_MODE_OUTPUT);

    gpio_reset_pin(button);
    gpio_set_direction(button, GPIO_MODE_INPUT);
    gpio_pullup_en(button);

    while (1)
    {
        int button_state = gpio_get_level(button);

        if (button_state == 0)
            gpio_set_level(led, 1);
        else
            gpio_set_level(led, 0);
        vTaskDelay(pdMS_TO_TICKS(500));


    }
}

/* ---------- ISR HANDLER ---------- */
static gpio_num_t isr_led_pin;
static void IRAM_ATTR button_isr_handler(void* arg)
{
    led_state = !led_state;
    gpio_set_level(isr_led_pin, led_state);
}

/* ---------- INTERRUPT INIT ---------- */
void gpio_button_interrupt_init(gpio_num_t led_pin, gpio_num_t button_pin)
{

    gpio_reset_pin(led_pin);
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);
    isr_led_pin = led_pin;

    gpio_reset_pin(button_pin);
    gpio_set_direction(button_pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(button_pin, GPIO_PULLUP_ONLY);
    gpio_set_intr_type(button_pin, GPIO_INTR_NEGEDGE);

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