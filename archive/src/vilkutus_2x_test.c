// vim: foldmethod=marker ft=c

// Tuodaan muut tiedostot.
#include "lediportit_2x.h"
#include <avr/io.h>
#include <stdint.h>
#include <util/delay_basic.h>
int8_t kirkkaus[64] = { 0 };

// PWM Ajoitukset cycles {{{

// 1 / 8MHz --> 0.125us
// Loop_2 on 4 cyclen verran
// Eli esim. 624 * 0.125 * 4 cycleä = 312uS
// Nollat tässä tapauksessä ei käytetä

// Kirkas vaihe
const int16_t K_VAIHEET
    [16] = { 0, 1, 2, 3, 4, 8, 16, 28, 52, 100, 160, 220, 320, 400, 500, 624 };

/// Pimeä vaihe
const int16_t P_VAIHEET[16] = {
    624,
    623,
    622,
    621,
    620,
    616,
    608,
    596,
    572,
    524,
    464,
    404,
    304,
    224,
    124,
    0,
};

// Backup
// const int16_t P_VAIHEET[16] = {
//     624,
//     624 - K_VAIHEET[1],
//     624 - K_VAIHEET[2],
//     624 - K_VAIHEET[3],
//     624 - K_VAIHEET[4],
//     624 - K_VAIHEET[5],
//     624 - K_VAIHEET[6],
//     624 - K_VAIHEET[7],
//     624 - K_VAIHEET[8],
//     624 - K_VAIHEET[9],
//     624 - K_VAIHEET[10],
//     624 - K_VAIHEET[11],
//     624 - K_VAIHEET[12],
//     624 - K_VAIHEET[13],
//     624 - K_VAIHEET[14],
//     0,
// };

// }}}

// Ledien vikuttaminen {{{
void vilkutus(void) {
    uint8_t led1 = 0b00000001;
    uint8_t led2 = 0b00010000;
    int8_t *kirkptr1;
    int8_t *kirkptr2;
    int8_t kirk1;
    int8_t kirk2;
    uint8_t sarake = 0;
    uint8_t pari = 0;
    uint8_t *pbptr;

    uint16_t delay1;
    uint16_t delay2;
    uint16_t delay3;

    uint8_t vaihto;
    uint8_t tila;

    kirkptr1 = &kirkkaus[0]; // kirkkaustaulukon pointteri
    kirkptr2 = &kirkkaus[32];
    pbptr = &pb[0];

    PORTA = alloff_pa;
    PORTB = alloff_pb;

    for (sarake = 0; sarake <= 7; sarake++) {

        for (pari = 0; pari <= 3; pari++) {

            // PRE-CALC --------------------------------------------------

            // Hankitaan ledien kirkkausarvot, ettei joka kerta tarttee hakea taulukosta
            kirk1 = *kirkptr1;
            kirk2 = *kirkptr2;

            // Asetetaan mitkä rivit menee päälle
            if (kirk1 != 0)
                PORTA |= (led1);

            if (kirk2 != 0)
                PORTA |= (led2);

            // Lasketaan etukäteen delay arvot ja tilat..

            // Kos kumpikin ledi off
            if (PORTA == 0) {
                delay1 = P_VAIHEET[0];
                tila = 0;
            }
            // Jos kumpikin tai toinen max kirkkaus
            else if ((kirk1 == 15 && kirk2 == 15) ||
                     (kirk1 == 0 && kirk2 == 15) ||
                     (kirk1 == 15 && kirk2 == 0)) {
                delay1 = K_VAIHEET[15];
                tila = 1;
            }
            // Jos kumpikin tai yksi ledi samaa kirkkautta  välillä 1-14
            else if (kirk1 == kirk2 || kirk1 == 0 || kirk2 == 0) {
                int8_t active = (kirk1 != 0) ? kirk1 : kirk2;
                delay1 = K_VAIHEET[active];
                delay2 = P_VAIHEET[active];
                tila = 2;
            }
            // Jos ledi 1 on kirkkaampi kuin 2, mutta kumpikin palaa
            else if (kirk1 > kirk2) {
                delay1 = K_VAIHEET[kirk2];
                delay2 = K_VAIHEET[kirk1] - delay1;
                delay3 = P_VAIHEET[kirk1];
                vaihto = led1;
                tila = 3;
            }
            // Sama mutta inverted
            else if (kirk1 < kirk2) {
                delay1 = K_VAIHEET[kirk1];
                delay2 = K_VAIHEET[kirk2] - delay1;
                delay3 = P_VAIHEET[kirk2];
                vaihto = led2;
                tila = 3;
            }

            // Varsinainen ledien vilkuttaminen --------------------------

            switch (tila) {
                case 0:
                    _delay_loop_2(delay1);
                    break;
                case 1:
                    PORTB = *pbptr;
                    _delay_loop_2(delay1);

                    PORTA = alloff_pa;
                    break;
                case 2:
                    PORTB = *pbptr;
                    _delay_loop_2(delay1);

                    PORTA = alloff_pa;
                    _delay_loop_2(delay2);
                    break;
                case 3:
                    PORTB = *pbptr;
                    _delay_loop_2(delay1);
                    PORTA = vaihto;
                    _delay_loop_2(delay2);

                    PORTA = alloff_pa;
                    _delay_loop_2(delay3);
                    break;
            }

            // Seuraavien rivien setuppiin -------------------------------

            // Siirry seuraavaan kirkkaustalukon pointteriin offsetilla
            kirkptr1 += 8;
            kirkptr2 += 8;

            // Siirry seuraavaan riviin
            led1 <<= 1;
            led2 <<= 1;
        }
        // Seuraavan sarakkeen setupppi
        pbptr++;

        // Siirry seuraavaan kirkkaustalukon pointteriin offsetilla
        // Ekan sarakkeen jälkeen, toisen sarakkeen ledit palaa... jne.
        kirkptr1 -= 31;
        kirkptr2 -= 31;

        // Laitetaan ensmmäiset ledi rivit
        led1 = init_pa_1;
        led2 = init_pa_2;
    }
}
// }}}
