#include "pico/stdlib.h"

#ifndef SPC_700_H
#define SPC_700_H

// Control pins
#define PIN_READ      16
#define PIN_WRITE     17

// Address lines
#define PIN_ADDR_PA7  18
#define PIN_ADDR_PA6  19
#define PIN_ADDR_PA1  20
#define PIN_ADDR_PA0  21

// The SPC's public address registers ($F4-$F7 internally, mapped via PA0-1)
#define PORT_0        0b00
#define PORT_1        0b01
#define PORT_2        0b10
#define PORT_3        0b11

// Data lines
#define PIN_DATA_0     8
#define PIN_DATA_1     9
#define PIN_DATA_2    10
#define PIN_DATA_3    11
#define PIN_DATA_4    12
#define PIN_DATA_5    13
#define PIN_DATA_6    14
#define PIN_DATA_7    15

// Pin masks
#define DATA_PINS_MASK 0b0000001111111100000000
#define CTRL_PINS_MASK 0b0000110000000000000000
#define ADDR_PINS_MASK 0b1111000000000000000000

#define DATA_BIT_OFFSET    8

void spc_init();
uint8_t spc_read(uint8_t port);

#endif
