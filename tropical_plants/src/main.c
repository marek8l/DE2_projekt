/**
 * @file main.c
 * @brief Smart Flower Watering System - AVR - Digital Electronics 2
 * @date 25-11-2024
 *
 * @author Petr Kaplan
 * @author Marek Ivan
 * @author Miroslav Trchalik
 * @author Jakub Krivanek
 */

#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include <adc.h>
#include <gpio.h>
#include <oled.h>
#include <twi.h>
#include <uart.h>
#include "config.h"


// MACROS

#define FAN PB1 // pin 9
#define LIGHT PB0   // pin 8
#define HEATER PB2  // pin 10

#define DHT12_ADR 0x5c  // peripheral address of DHT12 sensor
#define DHT12_MEM 0x00  // offset to access the data of DHT12 sensor

// Macros to setup the Light-intensity sensor
// viz https://www.mouser.com/datasheet/2/348/bh1750fvi-e-186247.pdf?srsltid=AfmBOopXsNbrXH805bf72KnvAvOjhtHIuWU8JnSg7seawDr_eOblLK1S
#define BH1750_ADR 0x23 // peripheral address of BH1750 sensor
#define BH1750_MEM 0x10 // offset to access the data of BH1750 sensor
#define BH1750_POWER_ON 0x01    // hexadecimal value to init BH1750

// BH1750 light-intensity resolution mode;
// Set to Continuous High-Res Mode
#define BH1750_RES_MODE 0x10

#define OVF_CNT 4 // interrupt every OVF_CNT * timer overflow interval units

#define DRY 375   // if x > DRY then the soil is DRY; otherwise WET

// BH1750 returns value in Big-Endian order
// so we need to shift the lower byte up 8 times to the left
// to get the full 16 bit value it contains
#define BH1750_VALUE (bh1750_values[0] << 8 | bh1750_values[1])

// GLOBAL VARS

volatile bool new_data = false;  // will change value every n-th time interval based on OVF_CNT
volatile uint8_t dht12_values[5];   // array to store data from dht12
volatile uint8_t bh1750_values[2];  // array to store data from bh1750
uint16_t adc_data;  // variable to store data from ADC moisture sensor

// temp buffer for printing data, needs to be of length 6
// (max possible value is 65535 - length of 5)
// so the '\0' will be kept at the end of a string
char buffer[6];

// INTERRUPT ROUTINE

/**
 * @brief Interrupt Routine processed every time period second based on the timer
 */
ISR(TIMER1_OVF_vect) {
    static uint8_t n_ovfs = 0;
    n_ovfs++;
    if (n_ovfs >= OVF_CNT) { // Will be executed every OVF_CNT * overflow interval
        ADCSRA |= (1 << ADSC);
        new_data = true;
        n_ovfs = 0;
    }
}

// FUNCTION DEFINITIONS

/**
 * @brief Initialize Light-intensity sensor BH1750
 * @note The sensor must be connected to Vcc=3.3V
 */
void bh1750_init() {
    // Power on the light sensor
    twi_start();
    if (twi_write((BH1750_ADR << 1) | TWI_WRITE) == 0) {
        twi_write(BH1750_POWER_ON);
        twi_stop();
        uart_puts("BH1750 powered on\n");
    }
    else {
        uart_puts("Failed to power on the BH1750 sensor\n");
    }
    // Set the light intensity resolution mode
    twi_start();
    if (twi_write((BH1750_ADR << 1) | TWI_WRITE) == 0) {
        twi_write(BH1750_RES_MODE);
        twi_stop();
        uart_puts("BH1750 set to High resolution mode\n");
    }
    else {
        uart_puts("Failed to set the resolution mode of BH1750\n");
    }
}


/**
 * @brief Initialize OLED display
 * @note Prints the static content
 */
void oled_setup() {
    oled_init(OLED_DISP_ON);
    oled_clrscr();

    oled_charMode(NORMALSIZE);
    oled_gotoxy(0, 0);
    oled_puts("Temperat [°C]:");
    oled_gotoxy(0, 1);
    oled_puts("Humidity [\%]:");
    oled_gotoxy(0, 2);
    oled_puts("Light   [lx]:");
    oled_gotoxy(0, 3);
    oled_puts("Soil State  :");

    oled_display();
}


/**
 * @brief Update proccessed data from all connected sensors
 */
void update_data() {
    twi_readfrom_mem_into(DHT12_ADR, DHT12_MEM, dht12_values, 5);
    twi_readfrom_mem_into(BH1750_ADR, BH1750_MEM, bh1750_values, 2);
    adc_data = get_adc_data();
}


/**
 * @brief Update dynamic content on the OLED display
 */
void oled_update() {
    // Display new temperature data
    oled_charMode(NORMALSIZE);
    oled_gotoxy(14, 0);
    sprintf(buffer, "%3d.%01u", (int8_t)(dht12_values[2]), dht12_values[3]);
    oled_puts(buffer);

    // Display new air-humidity data
    oled_gotoxy(14, 1);
    sprintf(buffer, "%3u.%01u", dht12_values[0], dht12_values[1]);
    oled_puts(buffer);

    // Display new light intensity data
    oled_gotoxy(14, 2);
    sprintf(buffer, "%5u", BH1750_VALUE);
    oled_puts(buffer);

    // Display soil moisture state
    oled_gotoxy(15, 3);
    sprintf(buffer, "%4s", adc_data >= DRY ? "DRY" : "WET");
    oled_puts(buffer);
}


/**
 * @brief Print dynamic content to UART interface
 */
void uart_update() {
    uart_putc('\n');
    itoa((int8_t)(dht12_values[2]), buffer, 10);
    uart_puts("Temperature     ");
    uart_puts(buffer);
    uart_puts(".");

    itoa(dht12_values[3], buffer, 10);
    uart_puts(buffer);
    uart_puts(" °C\n");

    itoa(dht12_values[0], buffer, 10);
    uart_puts("Air-Humidity    ");
    uart_puts(buffer);
    uart_puts(".");

    itoa(dht12_values[1], buffer, 10);
    uart_puts(buffer);
    uart_puts(" \%\n");

    uart_puts("Light-Intensity ");
    utoa(BH1750_VALUE, buffer, 10);
    uart_puts(buffer);
    uart_puts(" lx\n");

    uart_puts("Soil-Moisture   ");
    uart_puts(adc_data >= DRY ? "DRY [" : "WET [");

    utoa(adc_data, buffer, 10);
    uart_puts(buffer);
    uart_puts("]\n");
}


/**
 * @brief Setup the GPIO pins for external devices
 */
void pin_setup() {
    GPIO_mode_output(&DDRB, FAN);
    GPIO_mode_output(&DDRB, LIGHT);
    GPIO_mode_output(&DDRB, HEATER);
    GPIO_write_low(&PORTB, FAN);
    GPIO_write_low(&PORTB, LIGHT);
    GPIO_write_low(&PORTB, HEATER);
}


/**
 * @brief Controller of cooling fan connected through GPIO
 */
void temperature_control() {
    if (dht12_values[2] >= HIGH_TEMPERATURE) {
        GPIO_write_high(&PORTB, FAN);
        uart_puts("FAN ON | ");
    }
    else {
        GPIO_write_low(&PORTB, FAN);
        uart_puts("FAN OFF | ");
    }

    if (dht12_values[2] < LOW_TEMPERATURE) {
        GPIO_write_high(&PORTB, HEATER);
        uart_puts("HEATER ON | ");
    }
    else {
        GPIO_write_low(&PORTB, HEATER);
        uart_puts("HEATER OFF | ");
    }
}


/**
 * @brief Controller of Light source connected through GPIO
 */
void light_control() {
    if (BH1750_VALUE <= LIGHT_SWITCH) {
        GPIO_write_high(&PORTB, LIGHT);
        uart_puts("LIGHT ON\n");
    }
    else {
        GPIO_write_low(&PORTB, LIGHT);
        uart_puts("LIGHT OFF\n");
    }
}


/**
 * @brief Controller displaying message on the OLED when the soil is DRY
 */
void watering_control() {
    static bool flicker = false;
    oled_gotoxy(0, 6);
    oled_charMode(DOUBLESIZE);
    if (adc_data >= DRY) {
        oled_puts(" WATER ME!");
        oled_invert(flicker);
        flicker = !flicker;
    }
    else {
        oled_puts("          ");
        flicker = false;
        oled_invert(flicker);
    }
}

// MAIN LOOP

int main(void) {
    twi_init(); // initialize i2c/twi

    uart_init(UART_BAUD_SELECT(115200, F_CPU)); // initialize UART channel with PC
    uart_puts("MCU START\n");
    // initialize the adc moisture sensor and light sensor
    adc_init();
    bh1750_init();

    pin_setup(); // setup external device pinout

    TIM1_ovf_262ms();   // setup timer interrupts
    TIM1_ovf_enable();

    sei();      // set the global interrupt mask to enable interrupts

    oled_setup();     // display static content on OLED

    while (true) {  // infinite loop
        if (new_data) {    // if the set time interval has passed
            update_data();  // get new data from sensors
            uart_update();  // send the new data through UART channel
            oled_update();  // display the new data on OLED

            // react to new data with controllers
            temperature_control();
            light_control();
            watering_control();

            oled_display(); // show the changed context on OLED

            new_data = false;       // wait till the new_data is set to 1 again
        }
    }
    return 0;       // will never reach this
}
