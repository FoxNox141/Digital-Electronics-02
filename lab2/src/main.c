/***********************************************************************
 * 
 * Blink a LED in Arduino-style and use function from the delay library.
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2022 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_GREEN PB5
#define LED_BLUE PB0   // PB5 is AVR pin where green on-board LED 
                        // is connected
#define BUTTON PD2
//#define LED_RED PB1
#define SHORT_DELAY 500 // Delay in milliseconds
#ifndef F_CPU
#define F_CPU 16000000 // CPU frequency in Hz required for delay funcs
#endif

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>     // AVR device-specific IO definitions
#include <util/delay.h> // Functions for busy-wait delay loops
#include <gpio.h>

// -----
// This part is needed to use Arduino functions but also physical pin
// names. We are using Arduino-style just to simplify the first lab.
// #include "Arduino.h"

// #define PB5 13          // In Arduino world, PB5 is called "13"
// #define PB0 8
// #define PB1 9
// -----


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle one LED and use delay library.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    uint8_t led_value = 0;  // Local variable to keep LED status

    // Set pin where on-board LED is connected as output
    // pinMode(LED_GREEN, OUTPUT);
    // pinMode(LED_BLUE, OUTPUT);
    // pinMode(LED_RED, OUTPUT);
    DDRB = DDRB | (1<<BUTTON);
    DDRB = DDRB | (1<<LED_BLUE);
    //DDRB = DDRB | (1<<LED_RED);
    DDRB = DDRB | (1<<LED_GREEN);

int main(void)
{
    uint8_t led_value = 0;  // Local variable to keep LED status

    // Set pins where LEDs are connected as output
    // Ver 1: Arduino style
    // pinMode(LED_GREEN, OUTPUT);
    // pinMode(LED_RED, OUTPUT);

    // Ver 2: Low-level (register) style
    // DDRB = DDRB | (1<<LED_GREEN);
    // DDRB = DDRB | (1<<LED_RED);

    // Ver 3: Library function style
    GPIO_mode_output(&DDRB, LED_GREEN);
    GPIO_mode_output(&DDRB, LED_BLUE);
    GPIO_mode_input_pullup(&DDRB, BUTTON);

}
    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(SHORT_DELAY);

        // Change LED value
        if (led_value == 0) {
            led_value = 1;
            // Set pin to HIGH
            //PORTB = PORTB | (1<<LED_BLUE);
            //PORTB = PORTB | (1<<LED_RED);
            //PORTB = PORTB | (1<<LED_GREEN);
            GPIO_write_high(&PORTB, LED_GREEN);
            GPIO_write_high(&PORTB, LED_BLUE);
            GPIO_write_low(&PORTB, BUTTON);
            // digitalWrite(LED_GREEN, HIGH);
            // digitalWrite(LED_BLUE, HIGH);
            // digitalWrite(LED_RED, LOW);
        }
        else {
            led_value = 0;
            // Clear pin to LOW
            //PORTB = PORTB & ~(1<<LED_BLUE);
            //PORTB = PORTB & ~(1<<LED_RED);
            //PORTB = PORTB & ~(1<<LED_GREEN);
            GPIO_write_low(&PORTB, LED_GREEN);
            GPIO_write_low(&PORTB, LED_BLUE);
            GPIO_write_high(&PORTB, BUTTON);
            //digitalWrite(LED_GREEN, LOW);
            //digitalWrite(LED_BLUE, LOW);
            //digitalWrite(LED_RED, HIGH);
        }
    }

    // Will never reach this
    return 0;
}