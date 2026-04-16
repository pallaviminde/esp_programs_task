#include "config.h"
#include "adc_driver.h"
// Moving Average
#define SAMPLE_COUNT 100

static int adc_buffer[SAMPLE_COUNT];
static int buffer_index = 0;
static int buffer_filled = 0;

// -------- Moving Average Function --------
static int moving_average(int new_sample)
{
    adc_buffer[buffer_index] = new_sample;
    buffer_index = (buffer_index + 1) % SAMPLE_COUNT;

    if (buffer_filled < SAMPLE_COUNT)
        buffer_filled++;

    int sum = 0;
    for (int i = 0; i < buffer_filled; i++)
        sum += adc_buffer[i];

    return sum / buffer_filled;
}

// -------- ADC Init --------
void adc_driver_init(adc1_channel_t channel, adc_atten_t atten, adc_bits_width_t width)
{
    adc1_config_width(width);
    adc1_config_channel_atten(channel, atten);
}

// -------- Voltage Read --------
float adc_get_voltage(adc1_channel_t channel)
{
    int raw = adc1_get_raw(channel);
    int filtered = moving_average(raw);

    float voltage = ((float)filtered / 4095.0) * VREF;
    return voltage;
}

// -------- Temperature Calculation --------
float adc_get_temperature(adc1_channel_t channel)
{
    float voltage = adc_get_voltage(channel);

    float rpt = (voltage * RREF) / (2.96 - voltage);
    float temperature = (rpt - 100.0) / 0.39;

    return temperature;
}