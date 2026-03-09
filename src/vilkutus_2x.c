// vim: foldmethod=marker ft=c

// Tuodaan muut tiedostot.
#include "lediportit_2x.h"
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <util/delay_basic.h>
int8_t kirkkaus[64] = { 0 };

// PWM Ajoitukset {{{

// Possusalaman delay arvoja puolittu,
// sillä ledejä on tuplasti, niin koko syklin aika on myös tuplasti pidempi.
// Arvot oli 312 ja olisi ollut ~ 50Hz
// Nyt:  156us * 64 ledejä ~> 100Hz.

// Kirkas vaihe
#define K1 0.0005
#define K2 0.1
#define K3 0.5
#define K4 1
#define K5 2
#define K6 4
#define K7 7
#define K8 13.5
#define K9 25
#define K10 40
#define K11 55
#define K12 80
#define K13 100
#define K14 125
#define K15 156

/// Pimeä vaihe
#define P0 156
#define P1 156 - K1
#define P2 156 - K2
#define P3 156 - K3
#define P4 156 - K4
#define P5 156 - K5
#define P6 156 - K6
#define P7 156 - K7
#define P8 156 - K8
#define P9 156 - K9
#define P10 156 - K10
#define P11 156 - K11
#define P12 156 - K12
#define P13 156 - K13
#define P14 156 - K14
// }}}

// PWM Ajoitukset cycles {{{

// 1 / 8MHz --> 0.125us

// Kirkas vaihe
const int K_VAIHEET
    [16] = { 1, 1, 2, 3, 4, 8, 16, 28, 52, 100, 160, 220, 320, 400, 500, 623 };

/// Pimeä vaihe
const int P_VAIHEET[16] = { 624,
    624 - K_VAIHEET[1],
    624 - K_VAIHEET[2],
    624 - K_VAIHEET[3],
    624 - K_VAIHEET[4],
    624 - K_VAIHEET[5],
    624 - K_VAIHEET[6],
    624 - K_VAIHEET[7],
    624 - K_VAIHEET[8],
    624 - K_VAIHEET[9],
    624 - K_VAIHEET[10],
    624 - K_VAIHEET[11],
    624 - K_VAIHEET[12],
    624 - K_VAIHEET[13],
    624 - K_VAIHEET[14],
    1 };
// }}}

// Ledien vikuttaminen {{{
void vilkutus(void) {
    uint8_t led1 = 0b00000001;
    uint8_t led2 = 0b00010000;
    int8_t *kirkptr1;
    int8_t *kirkptr2;
    uint8_t sarake = 0;
    uint8_t pari = 0;
    uint8_t *pbptr;

    kirkptr1 = &kirkkaus[0]; // kirkkaustaulukon pointteri
    kirkptr2 = &kirkkaus[32];
    pbptr = &pb[0];

    for (sarake = 0; sarake <= 7; sarake++) {
        PORTB = *pbptr; // Multiplexauksen sarake asetukset

        for (pari = 0; pari <= 3; pari++) {
            // _delay_ms(100);

            if (*kirkptr1 == 0 && *kirkptr2 == 0) {
                _delay_loop_2(P_VAIHEET[0]);
            }
            else if (*kirkptr1 == *kirkptr2) {
                PORTA |= (led1);
                PORTA |= (led2);
                _delay_loop_2(K_VAIHEET[*kirkptr1]);

                PORTA = 0b00000000;
                _delay_loop_2(P_VAIHEET[*kirkptr1]);
            }
            else if (*kirkptr1 == 0) {
                PORTA |= (led2);
                _delay_loop_2(K_VAIHEET[*kirkptr2]);

                PORTA = 0b00000000;
                _delay_loop_2(P_VAIHEET[*kirkptr2]);
            }
            else if (*kirkptr2 == 0) {
                PORTA |= (led1);
                _delay_loop_2(K_VAIHEET[*kirkptr1]);

                PORTA = 0b00000000;
                _delay_loop_2(P_VAIHEET[*kirkptr1]);
            }
            else if (*kirkptr1 > *kirkptr2) {
                PORTA |= (led1);
                PORTA |= (led2);
                _delay_loop_2(K_VAIHEET[*kirkptr2]);

                PORTA = (led1);
                _delay_loop_2(K_VAIHEET[*kirkptr1]); // Epäloogista ?

                PORTA = 0b00000000;
                _delay_loop_2(P_VAIHEET[*kirkptr1]);
            }
            else if (*kirkptr2 > *kirkptr1) {
                PORTA |= (led2);
                PORTA |= (led1);
                _delay_loop_2(K_VAIHEET[*kirkptr1]);

                PORTA = (led2);
                _delay_loop_2(K_VAIHEET[*kirkptr2]); // Epäloogista ?

                PORTA = 0b00000000;
                _delay_loop_2(P_VAIHEET[*kirkptr2]);
            }
            else {
                _delay_ms(10000);
            }
            kirkptr1 += 8;
            kirkptr2 += 8;
            led1 <<= 1;
            led2 <<= 1;
        }
        pbptr++; // Seuraava sarake
        // kirkptr1 = &kirkkaus[0]; // kirkkaustaulukon pointteri
        // kirkptr2 = &kirkkaus[32];
        kirkptr1 -= 31;
        kirkptr2 -= 31;
        led1 = 0b00000001;
        led2 = 0b00010000;
    }
}
// }}}
