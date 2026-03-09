// vim: foldmethod=marker ft=c

// Tuodaan muut tiedostot.
#include "lediportit.h"
#include <stdint.h>
#include <util/delay_basic.h>
int8_t kirkkaus[64] = { 0 };

// PWM Ajoitukset test {{{

// Samat ajoitukset taulukkomuodossa
// Jospa delay funtio toimisi näillä

// Possusalaman delay arvoja puolittu,
// sillä ledejä on tuplasti, niin koko syklin aika on myös tuplasti pidempi.
// Arvot oli 312 ja olisi ollut ~ 50Hz
// Nyt:  156us * 64 ledejä ~> 100Hz.

// 1 / 8MHz --> 0.125us

// Kirkas vaihe
const int K_VAIHEET[16] = { 0,
    1,
    1,
    1,
    1.0,
    2.0,
    4.0,
    7.0,
    13,
    25,
    40,
    55,
    80,
    100,
    125,
    156 };

/// Pimeä vaihe
const int P_VAIHEET[16] = { 156,
    155,
    155,
    155,
    155,
    154,
    152,
    149,
    143,
    131,
    116,
    101,
    76,
    56,
    31,
    0 };
// }}}

// Ledien vikuttaminen {{{
void vilkutus(void) {
    uint8_t led = 0;
    int8_t *kirkptr;
    uint8_t *paptr;
    uint8_t *pbptr;

    kirkptr = &kirkkaus[0]; // kirkkaustaulukon pointteri
    paptr = &pa[0];         // PortA taulukon pointteri
    pbptr = &pb[0];

    while (led < 64) {

        switch (*kirkptr) {
            case 0:
                _delay_loop_2(P_VAIHEET[*kirkptr]);
                break;

            case 1 ... 15:
                PORTA = *paptr;
                PORTB = *pbptr;
                _delay_loop_2(K_VAIHEET[*kirkptr]);

                PORTB = alloff_pb;
                _delay_loop_2(P_VAIHEET[*kirkptr]);
                break;

            default:
                break;
        }

        kirkptr++;
        paptr++;
        pbptr++;
        led++;
    }
}
// }}}
