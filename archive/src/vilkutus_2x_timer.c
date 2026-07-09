// vim: foldmethod=marker ft=c

// Tuodaan muut tiedostot.
#include <avr/io.h>
#include <stdint.h>
#include <util/delay_basic.h>

extern int8_t kirkkaus[64];

// "PWM" Ajoitukset (8-bit) {{{
// const uint8_t K_VAIHEET
//     [16] = { 0, 1, 10, 19, 28, 37, 46, 55, 64, 73, 82, 91, 100, 109, 118, 127 };

// const uint8_t K_VAIHEET
//     [16] = { 0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 82, 91, 100, 109, 118, 127 };

const uint8_t K_VAIHEET
    [16] = { 0, 1, 2, 4, 5, 10, 15, 21, 29, 39, 51, 65, 82, 101, 122, 127 };

// const uint8_t K_VAIHEET[16] = { 0,
//     1,
//     3,
//     7,
//     13,
//     22,
//     35,
//     51,
//     73,
//     100,
//     132,
//     171,
//     213,
//     230,
//     245,
//     255 };

// Portti asetukset {{{

// Multiplexauksen ekat ledit
uint8_t init_pa_1 = 0b00000001;
uint8_t init_pa_2 = 0b00010000;

// Pinnit off tilassa 76543210
uint8_t alloff_pa = 0b00000000;
uint8_t alloff_pb = 0b11111111;

// B PORTIT
uint8_t pb[8] = {
    0b11111110,
    0b11111101,
    0b11111011,
    0b11110111,
    0b11101111,
    0b11011111,
    0b10111111,
    0b01111111,
};
// }}}

// Ledien vikuttaminen {{{
void vilkutus(void) {
    uint8_t led1 = init_pa_1;
    uint8_t led2 = init_pa_2;
    int8_t *kirkptr1;
    int8_t *kirkptr2;
    int8_t kirk1;
    int8_t kirk2;
    uint8_t sarake;
    uint8_t pari;
    uint8_t *pbptr;
    int16_t taimeri;

    kirkptr1 = &kirkkaus[0]; // kirkkaustaulukon pointteri
    kirkptr2 = &kirkkaus[32];
    pbptr = &pb[0];

    PORTA = alloff_pa;
    PORTB = alloff_pb;

    for (sarake = 0; sarake <= 7; sarake++) {

        for (pari = 0; pari <= 3; pari++) {

            // Preppaus --------------------------------------------------

            // Hankitaan ledien kirkkausarvot, ettei joka kerta tarttee hakea taulukosta
            kirk1 = K_VAIHEET[*kirkptr1];
            kirk2 = K_VAIHEET[*kirkptr2];

            PORTB = *pbptr;

            // Asetetaan rivit päälle saman tien...
            if (kirk1 >= 5)
                PORTA |= (led1);

            if (kirk2 >= 5)
                PORTA |= (led2);

            // Nämä ovat pika vilkutukset jolla saa vielä pimeämmät gradienttit
            if (kirk1 == 1) {
                PORTA |= led1;
                PORTA &= ~led1;
            }

            if (kirk2 == 1) {
                PORTA |= led2;
                PORTA &= ~led2;
            }

            if (kirk1 == 2) {
                PORTA |= led1;
                _delay_loop_1(8);
                PORTA &= ~led1;
            }

            if (kirk2 == 2) {
                PORTA |= led2;
                _delay_loop_1(8);
                PORTA &= ~led2;
            }

            if (kirk1 == 4) {
                PORTA |= led1;
                _delay_loop_1(16);
                PORTA &= ~led1;
            }

            if (kirk2 == 4) {
                PORTA |= led2;
                _delay_loop_1(16);
                PORTA &= ~led2;
            }

            // Varsinainen ledien vilkuttaminen --------------------------

            // Sarake auki
            // PORTB = *pbptr;

            // Härskä taimeri setuppi, mutta helposti laajentavissa
            for (taimeri = 0; taimeri <= 127; taimeri++) {

                // Laittaa nollan PORTA:han jos ledi poistuu
                if (taimeri == kirk1) {
                    PORTA &= ~(led1);
                }

                if (taimeri == kirk2) {
                    PORTA &= ~(led2);
                }
            }

            // Suljetaan rivit ja sarakkeet
            PORTA = alloff_pa;
            PORTB = alloff_pb;

            // Seuraavien rivien setuppiin -------------------------------

            // Siirry seuraavaan kirkkaustalukon pointteriin offsetilla
            kirkptr1 += 8;
            kirkptr2 += 8;

            // Siirry seuraavaan riviin
            led1 <<= 1;
            led2 <<= 1;
        }

        // Seuraavan sar§akkeen setupppi ----------------------------------
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
