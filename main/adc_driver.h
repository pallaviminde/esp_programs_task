#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include <stdint.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "config.h"


#define ADC_CH     ADC1_CHANNEL_5
#define ADC_ATT    ADC_ATTEN_DB_11
#define ADC_WID    ADC_WIDTH_BIT_12

#define VREF 3.3
#define RREF 100.0

// Public functions
void adc_driver_init(adc1_channel_t channel, adc_atten_t atten, adc_bits_width_t width);
float adc_get_voltage(adc1_channel_t channel);
float adc_get_temperature(adc1_channel_t channel);

#endif