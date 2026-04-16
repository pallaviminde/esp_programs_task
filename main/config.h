#ifndef CONFIG_H
#define CONFIG_H


//gpio pin definations
//#define LED_pin GPIO_NUM_4
#define LED_PIN1 GPIO_NUM_4
#define LED_PIN2 GPIO_NUM_5
#define BUTTON_PIN GPIO_NUM_37

//adc values definations
#define ADC_CH  ADC1_CHANNEL_5
#define ADC_ATT ADC_ATTEN_DB_11
#define ADC_WID ADC_WIDTH_BIT_12
#define VREF 3.3
#define RREF 100.0

//uart pin definations
#define UART_PORT UART_NUM_1
#define UART_TX_PIN 43 
#define UART_RX_PIN 44
#define UART_BAUD_RATE 115200

#endif

