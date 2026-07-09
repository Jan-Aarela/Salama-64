// vim: foldmethod=marker ft=c

// Tuodaan muut tiedostot.
#include <avr/io.h>
#include <stdint.h>
#include <util/delay_basic.h>

extern int8_t kirkkaus[64];

// "PWM" Ajoitukset {{{
const uint8_t K_VAIHEET
    [16] = { 0, 1, 2, 4, 5, 10, 15, 21, 29, 39, 51, 65, 82, 101, 122, 127 };

//  }}}

// Ledi configuraatiot {{{
// NOTE: Vasemman puoleinen anodi
// Oikea katodi

uint8_t ledi_configuraatio[32][2] = {

    // 1. Pysty rivi (SKEMA)
    { 6, 0 },
    { 0, 6 },
    { 6, 1 },
    { 1, 6 },
    { 6, 2 },
    { 2, 6 },
    { 6, 3 },
    { 3, 6 },
    { 6, 4 },
    { 4, 6 },
    { 6, 5 },
    { 5, 6 },

    // 2. ...
    { 5, 0 },
    { 0, 5 },
    { 5, 1 },
    { 1, 5 },
    { 5, 2 },
    { 2, 5 },
    { 5, 3 },
    { 3, 5 },
    { 5, 4 },
    { 4, 5 },

    // 3. ...
    { 4, 0 },
    { 0, 4 },
    { 4, 1 },
    { 1, 4 },
    { 4, 2 },
    { 2, 4 },
    { 4, 3 },
    { 3, 4 },

    // 4. ...
    { 3, 0 },
    { 0, 3 }
};

// }}}

// Ledi päälle {{{
void A_on(uint8_t ledi_1) {
    uint8_t high_pin = ledi_configuraatio[ledi_1][0];
    uint8_t low_pin = ledi_configuraatio[ledi_1][1];

    DDRA = (1 << high_pin) | (1 << low_pin);
    PORTA = (1 << high_pin);
}

void B_on(uint8_t ledi_2) {
    uint8_t high_pin = ledi_configuraatio[ledi_2][0];
    uint8_t low_pin = ledi_configuraatio[ledi_2][1];

    DDRB = (1 << high_pin) | (1 << low_pin);
    PORTB = (1 << high_pin);
}

// }}}

// Ledi pois päältä {{{

// PORT A ledit
void A_off(void) {
    PORTA = 0x00;
    DDRA = 0x00;
}

// PORT B ledit
void B_off(void) {
    PORTB = 0x00;
    DDRB = 0x00;
}
// }}}

// Ledien vikuttaminen {{{
void vilkutus(void) {
    int8_t *kirkptr1;
    int8_t *kirkptr2;
    int8_t kirk1;
    int8_t kirk2;
    uint8_t pari;
    int16_t taimeri;

    kirkptr1 = &kirkkaus[0]; // kirkkaustaulukon pointteri
    kirkptr2 = &kirkkaus[13];

    for (pari = 0; pari <= 31; pari++) {

        // Preppaus --------------------------------------------------

        // Hankitaan ledien kirkkausarvot, ettei joka kerta tarttee hakea taulukosta
        kirk1 = K_VAIHEET[*kirkptr1];
        kirk2 = K_VAIHEET[*kirkptr2];

        // Asetetaan rivit päälle saman tien...

        if (kirk1 == 1) {
            A_on(pari);
            A_off();
        }

        if (kirk1 == 2) {
            A_on(pari);
            _delay_loop_1(8);
            A_off();
        }

        if (kirk1 == 4) {
            A_on(pari);
            _delay_loop_1(16);
            A_off();
        }

        if (kirk2 == 1) {
            B_on(pari);
            B_off();
        }

        if (kirk2 == 2) {
            B_on(pari);
            _delay_loop_1(8);
            B_off();
        }

        if (kirk2 == 4) {
            B_on(pari);
            _delay_loop_1(16);
            B_off();
        }

        if (kirk1 >= 5) {
            A_on(pari);
        }

        if (kirk2 >= 5) {
            B_on(pari);
        }

        // Varsinainen ledien vilkuttaminen --------------------------

        // Härskä taimeri setuppi, mutta helposti laajentavissa
        for (taimeri = 0; taimeri <= 127; taimeri++) {

            // Laittaa nollan PORTA:han jos ledi poistuu
            if (taimeri == kirk1) {
                A_off();
            }

            if (taimeri == kirk2) {
                B_off();
            }
        }

        // Ledit pois päältä
        A_off();
        B_off();

        // Seuraavien ledien setuppiin -------------------------------

        // Siirry seuraavaan kirkkaustalukon pointteriin offsetilla
        kirkptr1++;
        kirkptr2++;

        // if (*kirkptr1 == 10) {
        //     kirkptr1 += 31;
        // }

        if ((kirkptr1 - kirkkaus) == 13) {
            kirkptr1 = &kirkkaus[45];
        }
    }
} // }}}
