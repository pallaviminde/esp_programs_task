#include "config.h"      // Contains VREF, RREF definitions
#include "adc_driver.h"  // Contains function prototypes

// Moving Average
#define SAMPLE_COUNT 100

// Buffer to store ADC samples
static int adc_buffer[SAMPLE_COUNT];
// Current index in circular buffer
static int buffer_index = 0;
// Number of valid samples in buffer
static int buffer_filled = 0;

// -------- Moving Average Function --------
static int moving_average(int new_sample)
{
    // Store new sample in buffer
    adc_buffer[buffer_index] = new_sample;
    // Move index forward (wrap around using modulo)
    buffer_index = (buffer_index + 1) % SAMPLE_COUNT;

    // Increase filled count until buffer is full
    if (buffer_filled < SAMPLE_COUNT)
        buffer_filled++;

    // Calculate sum of samples
    int sum = 0;
    for (int i = 0; i < buffer_filled; i++)
        sum += adc_buffer[i];

    // Return average value
    return sum / buffer_filled;
}

/*
 * Function: adc_driver_init
 * Initializes ADC channel with specified configuration.
 * channel: ADC1 channel (e.g., ADC1_CHANNEL_0)
 * atten  : Attenuation level (input voltage range)
 * width  : ADC resolution (e.g., 12-bit)
 */
void adc_driver_init(adc1_channel_t channel, adc_atten_t atten, adc_bits_width_t width)
{
    // Configure ADC resolution (e.g., 12-bit → 0–4095)
    adc1_config_width(width);
    // Configure channel attenuation (affects measurable voltage range)
    adc1_config_channel_atten(channel, atten);
}

/*
 * Function: adc_get_voltage
 * Reads ADC value, applies filtering, and converts to voltage.
 * channel: ADC1 channel
 * returns: voltage in volts
 */
float adc_get_voltage(adc1_channel_t channel)
{
    // Read raw ADC value
    int raw = adc1_get_raw(channel);
    // Apply moving average filter
    int filtered = moving_average(raw);

    // Convert ADC value to voltage
    // 4095 → max value for 12-bit ADC
    float voltage = ((float)filtered / 4095.0) * VREF;
    return voltage;
}

/*
 * Function: adc_get_temperature
 * Calculates temperature from sensor voltage.
 * channel: ADC1 channel
 * returns: temperature (°C)
 * Notes:
 * - Uses sensor-specific formula
 * - RREF: reference resistor value
 */
float adc_get_temperature(adc1_channel_t channel)
{
    // Get measured voltage
    float voltage = adc_get_voltage(channel);

    // Calculate sensor resistance (RPT) using voltage divider formula
    float rpt = (voltage * RREF) / (2.96 - voltage);
    // Convert resistance to temperature (sensor-specific equation)
    float temperature = (rpt - 100.0) / 0.39;

    return temperature;
}