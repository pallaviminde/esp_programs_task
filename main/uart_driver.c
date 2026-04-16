#include "uart_driver.h"
#include "config.h"

// Simple UART command interface with authentication and LED control
#define PASSWORD "1234"
#define MAX_ATTEMPTS 3

// Track authentication state and wrong password attempts
static int is_authenticated = 0;
static int wrong_attempts = 0;

// Tag for logging
static const char *TAG = "UART1";

/* ---------- UART INITIALIZATION ---------- */
void led_init(void)
{
    gpio_set_direction(LED_PIN1, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN1, 0);
}

/*
 * Function: uart_init
 * Initializes UART with configured parameters:
 * - Baud rate
 * - Data bits
 * - Parity
 * - Stop bits
 */
void uart_init(void)
{
    uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    // Install UART driver and configure parameters
    uart_driver_install(UART_PORT, 1024, 1024, 0, NULL, 0);
    // Configure UART parameters (baud rate, data bits, parity, stop bits)
    uart_param_config(UART_PORT, &uart_config);
    // Set UART pins (TX, RX, RTS, CTS)
    uart_set_pin(UART_PORT, UART_TX_PIN, UART_RX_PIN,
                 UART_PIN_NO_CHANGE,
                 UART_PIN_NO_CHANGE);

    ESP_LOGI(TAG, "UART Initialized Successfully");
}

/*
 * Function: transmit_string
 * Sends a string over UART.
 * data: null-terminated string
 */
void transmit_string(const char *data)
{
    uart_write_bytes(UART_PORT, data, strlen(data));
}

/*
 * Function: receive_string
 * FreeRTOS task for UART receive and command processing.
 * Features:
 * - Login authentication system
 * - Command-line interface (CLI)
 * - LED control via commands
 */
void receive_string(void *arg)
{
    uint8_t data[128];  // Buffer for incoming UART data
    char cmd[20];       // Buffer for parsed command
    char input_pass[20]; // Buffer for password input

    // Initial login prompt
    transmit_string("\r\n--- LOGIN REQUIRED ---\r\nEnter Password:\r\n> ");

    while (1)
    {
        // Read data from UART with a timeout
        int len = uart_read_bytes(UART_PORT, data, sizeof(data)-1, pdMS_TO_TICKS(100));

        if (len > 0)
        {
            // Null-terminate the received data and remove any trailing newline characters
            data[len] = '\0';
            data[strcspn((char *)data, "\r\n")] = 0;

            // ================= LOGIN MODE =================
            if (!is_authenticated)
            {
                // Parse password input (up to 19 characters to prevent overflow)
                sscanf((char *)data, "%19s", input_pass);

                // Check if entered password matches the predefined password
                if (strcmp(input_pass, PASSWORD) == 0)
                {
                    is_authenticated = 1;
                    wrong_attempts = 0;  // reset counter

                    transmit_string("\r\nAccess Granted!\r\n");
                    transmit_string("Welcome\r\n");
                    transmit_string("\r\n--- DEBUG SHELL ---\r\nType HELP\r\n> ");
                }
                else
                {
                    wrong_attempts++;
                    transmit_string("Wrong Password!\r\n");

                    // If maximum wrong attempts reached, lock the system for 10 seconds
                    if (wrong_attempts >= MAX_ATTEMPTS)
                    {
                        transmit_string("System Locked for 10 seconds!\r\n");
                        vTaskDelay(pdMS_TO_TICKS(10000));
                        wrong_attempts = 0; // reset after lock
                    }

                    transmit_string("Enter Password:\r\n> ");
                }
            }
            // ================= COMMAND MODE =================
            else
            {
                int value;

                if (sscanf((char *)data, "%19s %d", cmd, &value) >= 1)
                {
                    // Process commands (e.g., LED ON/OFF, HELP)
                    if (strcmp(cmd, "LED") == 0)
                    {
                        if (value == 1)
                        {
                            gpio_set_level(LED_PIN1, 1);
                            transmit_string("LED ON\r\n");
                        }
                        else if (value == 0)
                        {
                            gpio_set_level(LED_PIN1, 0);
                            transmit_string("LED OFF\r\n");
                        }
                    }
                    else if (strcmp(cmd, "HELP") == 0)
                    {
                        transmit_string("Commands:\r\n");
                        transmit_string("LED 1 -> ON\r\n");
                        transmit_string("LED 0 -> OFF\r\n");
                    }
                    else
                    {
                        transmit_string("Unknown Command\r\n");
                    }
                }

                transmit_string("> ");
            }
        }

        // Small delay to prevent task starvation
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}