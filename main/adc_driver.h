#ifndef ADC_DRIVER_H   // Prevents multiple inclusion of this header file
#define ADC_DRIVER_H

#include <stdint.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"          // ADC driver
#include "config.h"             // Project-specific configuration (e.g., GPIO pins)

// ADC channel used for input
#define ADC_CH     ADC1_CHANNEL_5
// ADC attenuation (defines input voltage range)
#define ADC_ATT    ADC_ATTEN_DB_11
// ADC resolution (12-bit → range 0–4095)
#define ADC_WID    ADC_WIDTH_BIT_12

// Reference voltage for ADC conversion (in volts)
#define VREF 3.3
// Reference resistor value used in sensor calculation (ohms)
#define RREF 100.0

/* ----------- Public Function Declarations ----------- */
/*
 * Function: adc_driver_init
 * Initializes ADC with specified channel, attenuation, and resolution.
 * channel: ADC1 channel
 * atten  : Attenuation level (input voltage range)
 * width  : ADC resolution (bit width)
 */
void adc_driver_init(adc1_channel_t channel, adc_atten_t atten, adc_bits_width_t width);
/*
 * Function: adc_get_voltage
 * Reads ADC value and converts it to voltage.
 * channel: ADC1 channel
 * returns: voltage in volts
 */
float adc_get_voltage(adc1_channel_t channel);
/*
 * Function: adc_get_temperature
 * Calculates temperature from ADC voltage reading.
 * channel: ADC1 channel
 * returns: temperature in degrees Celsius
 */
float adc_get_temperature(adc1_channel_t channel);

#endif