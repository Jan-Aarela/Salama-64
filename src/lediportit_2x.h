// vim: foldmethod=marker ft=c

// Tuodaan muut tiedostot.
#include <avr/io.h>
#include <stdint.h>

// Pinnit off tilassa 76543210
uint8_t alloff_pb = 0b11111111;

// B PORTIT {{{
uint8_t pb[8] = {
    0b11111110, // 1. led
    0b11111101,
    0b11111011,
    0b11110111,
    0b11101111,
    0b11011111,
    0b10111111,
    0b01111111,

};
// }}}
