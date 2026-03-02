// vim: foldmethod=marker ft=c

// Tuodaan muut tiedostot.
#include "lediportit.h"
#include <stdint.h>
#include <util/delay.h>
int8_t kirkkaus[64] = { 0 };

// Possusalaman delay arvoja puolittu,
// sillä ledejä on tuplasti, niin koko syklin aika on myös tuplasti pidempi.
// Arvot oli 312 ja olisi ollut ~ 50Hz
// Nyt:  156us * 64 ledejä -> 100Hz.

#define K0 0
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

/// pimeä vaihe
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
#define P15 0

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
            _delay_us(P0);
            break;
        case 1:
            PORTA = *paptr;
            PORTB = *pbptr;
            _delay_us(K1);
            PORTB = alloff_pb;
            _delay_us(P1);
            break;
        case 2:
            PORTA = *paptr;
            PORTB = *pbptr;
            _delay_us(K2);
            PORTB = alloff_pb;
            _delay_us(P2);
            break;
        case 3:
            PORTA = *paptr;
            PORTB = *pbptr;
            _delay_us(K3);
            PORTB = alloff_pb;
            _delay_us(P3);
            break;
        case 4:
            PORTA = *paptr;
            PORTB = *pbptr;
            _delay_us(K4);
            PORTB = alloff_pb;
            _delay_us(P4);
            break;
        case 5:
            PORTA = *paptr;
            PORTB = *pbptr;
            _delay_us(K5);
            PORTB = alloff_pb;
            _delay_us(P5);
            break;
        case 6:
            PORTA = *paptr;
            PORTB = *pbptr;
            _delay_us(K6);
            PORTB = alloff_pb;
            _delay_us(P6);
            break;
        case 7:
            PORTA = *paptr;
            PORTB = *pbptr;
            _delay_us(K7);
            PORTB = alloff_pb;
            _delay_us(P7);
            break;
        case 8:
            PORTA = *paptr;
            PORTB = *pbptr;
            _delay_us(K8);
            PORTB = alloff_pb;
            _delay_us(P8);
            break;
        case 9:
            PORTA = *paptr;
            PORTB = *pbptr;
            _delay_us(K9);
            PORTB = alloff_pb;
            _delay_us(P9);
            break;
        case 10:
            PORTA = *paptr;
            PORTB = *pbptr;
            _delay_us(K10);
            PORTB = alloff_pb;
            _delay_us(P10);
            break;
        case 11:
            PORTA = *paptr;
            PORTB = *pbptr;
            _delay_us(K11);
            PORTB = alloff_pb;
            _delay_us(P11);
            break;
        case 12:
            PORTA = *paptr;
            PORTB = *pbptr;
            _delay_us(K12);
            PORTB = alloff_pb;
            _delay_us(P12);
            break;
        case 13:
            PORTA = *paptr;
            PORTB = *pbptr;
            _delay_us(K13);
            PORTB = alloff_pb;
            _delay_us(P13);
            break;
        case 14:
            PORTA = *paptr;
            PORTB = *pbptr;
            _delay_us(K14);
            PORTB = alloff_pb;
            _delay_us(P14);
            break;
        case 15:
            PORTA = *paptr;
            PORTB = *pbptr;
            _delay_us(K15);
            PORTB = alloff_pb;
            break;
        default: // negatiiviset ajatellaan nolliksi
            break;
        }

        kirkptr++;
        paptr++;
        pbptr++;
        led++;
    }
}
