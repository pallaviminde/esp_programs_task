#ifndef CONFIG_H    // Prevents multiple inclusion of this header file
#define CONFIG_H


//gpio pin definations
//#define LED_pin GPIO_NUM_4
#define LED_PIN1 GPIO_NUM_4  // LED connected to GPIO4
#define LED_PIN2 GPIO_NUM_5  // LED connected to GPIO5
#define BUTTON_PIN GPIO_NUM_37  // Button connected to GPIO37 (input with pull-up)

//adc values definations
#define ADC_CH  ADC1_CHANNEL_5  // ADC channel for sensor analog input
#define ADC_ATT ADC_ATTEN_DB_11 // ADC attenuation (input voltage range)
#define ADC_WID ADC_WIDTH_BIT_12 // ADC resolution (12-bit → range 0–4095)
#define VREF 3.3                 // Reference voltage for ADC conversion (in volts)
#define RREF 100.0               // Reference resistor value used in sensor calculation (ohms)

//uart pin definations
#define UART_PORT UART_NUM_1     // UART port number
#define UART_TX_PIN 43           // UART TX pin (GPIO43)
#define UART_RX_PIN 44           // UART RX pin (GPIO44)
#define UART_BAUD_RATE 115200    // UART baud rate

#endif  // CONFIG_H