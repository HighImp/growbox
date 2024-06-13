
#include <inttypes.h>

#ifndef _HARDWARE_H
#define _HARDWARE_H

// ANALOG PINS
const char SOIL1 = A0; // PC0
const char SOIL2 = A1; // PC1
const char SOIL3 = A2; // PC2

// BUS_PINS
const char HUM1 = 17; // PC3
const char HUM2 = 18; // PC4
const uint8_t ONE_WIRE = 19; // PC5

// FAN_PINS
const uint8_t PWM1 = 0; // PD0
const uint8_t PWM2 = 1; // PD1
const uint8_t TACHO1 = 2; // PD2
const uint8_t TACHO2 = 3; // PD3

// LED PINS
const uint8_t LEDB = 6; // PD6
const uint8_t LEDA = 7; // PD7

// SWITCH_PINS
const uint8_t SWITCH1 = 25; // PE2
const uint8_t SWITCH2 = 26; // PE3

// DIRECT_COM_PINS
const uint8_t EX_IO1 = 23; // PE0
const uint8_t EX_IO2 = 24; // PE1

# endif
