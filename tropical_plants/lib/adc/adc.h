#ifndef ADC_H
#define ADC_H

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

/**
 * @brief Initialize ADC soil-moisture sensor
 * @author Tomas Fryza
 * @note source https://github.com/tomas-fryza/avr-course/blob/master/examples/adc/src/main.c
 */
void adc_init();

/**
 * @brief Get the data from the ADC sensor
 * @returns Value of the last AD conversion
 */
uint16_t get_adc_data();

#endif
