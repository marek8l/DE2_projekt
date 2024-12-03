#include <adc.h>

volatile bool new_adc_data = false;

/**
 * @brief Interrupt routine propagating that new data has been received
 */
ISR(ADC_vect) {
    new_adc_data = true;
}

/* @brief Initialize ADC soil-moisture sensor
 * @author Tomas Fryza
 * @note source https://github.com/tomas-fryza/avr-course/blob/master/examples/adc/src/main.c
 */
void adc_init() {
    // Configure Analog-to-Digital Convertion unit
    // Select ADC voltage reference to "AVcc with external capacitor at AREF pin"
    ADMUX = ADMUX | (1<<REFS0);
    // Select input channel ADC0 (voltage divider pin)
    ADMUX = ADMUX & ~(1<<MUX3 | 1<<MUX2 | 1<<MUX1 | 1<<MUX0);
    // Enable ADC module
    ADCSRA = ADCSRA | (1<<ADEN);
    // Enable conversion complete interrupt
    ADCSRA = ADCSRA | (1<<ADIE);
    // Set clock prescaler to 128
    ADCSRA = ADCSRA | (1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0);
}

uint16_t get_adc_data() {
    static uint16_t retval = 0;
    ADCSRA |= (1 << ADSC);  // Start the AD conversion
    if (new_adc_data) {
        retval = ADC;
        new_adc_data = false;
    }
    return retval;
}
