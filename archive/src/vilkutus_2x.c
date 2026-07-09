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
    // Alustus
    uint8_t led1 = init_pa_1;
    uint8_t led2 = init_pa_2;

    int8_t *kirkptr1;
    int8_t *kirkptr2;

    uint8_t delay1;
    uint8_t delay2;
    uint8_t delay3;

    uint8_t vaihto;

    uint8_t sarake;
    uint8_t pari;
    uint8_t *pbptr;

    // kirkkaustaulukoin pointterit
    kirkptr1 = &kirkkaus[0];
    kirkptr2 = &kirkkaus[32];

    // Sarakekeen pointteri
    pbptr = &pb[0];

    PORTA = alloff_pa;
    PORTB = alloff_pb;

    for (sarake = 0; sarake <= 7; sarake++) {

        for (pari = 0; pari <= 3; pari++) {

            // PRE-CALC --------------------------------------------------

            // Asetetaan mitkä rivit menee päälle
            if (*kirkptr1 != 0) {
                PORTA |= (led1);
            }
            if (*kirkptr2 != 0) {
                PORTA |= (led2);
            }

            // Asetetaan 3 ajoitusta ja toinen ledi mikä jatkaa palamista.
            if (*kirkptr2 > *kirkptr1) {
                delay1 = K_VAIHEET[*kirkptr1];
                delay2 = K_VAIHEET[*kirkptr2] - K_VAIHEET[*kirkptr1];
                delay3 = P_VAIHEET[*kirkptr2];
                vaihto = led2;
            }
            else {
                delay1 = K_VAIHEET[*kirkptr2];
                delay2 = K_VAIHEET[*kirkptr1] - K_VAIHEET[*kirkptr2];
                delay3 = P_VAIHEET[*kirkptr1];
                vaihto = led1;
            }

            // Varsinainen ledien vilkuttaminen --------------------------

            // Asetetaan mitkä sarakkeet päästää virtaa
            PORTB = *pbptr;

            // Ensin kummatkin (tai yksi) ledit palaa himmeämmän ledin verran
            // Jos himmeämmän verran ledi on 0 aikaa, niin skip
            if (delay1 != 0) {
                _delay_loop_2(delay1);
            }

            // Jos jompikumpi ledi palaa pitempään, asetaan portti niin että 1 ledi palaa
            if (delay2 != 0) {
                PORTA = vaihto;
                _delay_loop_2(delay2);
            }

            // Jos pidemmällä palaneella ledillä on pimeä vaihe, niin anna ledien sammua
            if (delay3 != 0) {
                PORTA = alloff_pa;
                _delay_loop_2(delay3);
            }

            // Resetoidaan portti asetukset
            PORTA = alloff_pa;
            PORTB = alloff_pb;

            // Seuraavien rivien setuppiin -------------------------------
            // Siirry seuraavaan kirkkaustalukon pointteriin offsetilla
            kirkptr1 += 8;
            kirkptr2 += 8;

            // Siirry seuraavaan riviin
            led1 <<= 1;
            led2 <<= 1;

            // Koska skemassa ledien järjestys on päin vittua,
            // Pitää olla 8 offset, että samalla sarakkeella palaa ledit.
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
