// vim: foldmethod=marker ft=c

// Teinpäs possu2 JÖÖTI version (lisäefekteillä).
// Efektien toiminta periaate sama, paitsi bufferi on 2x isompi kun 2x enemmän ledjä.
// Vaikka ISR olisi ollut ehkä parempi, tämä ei "riko" nykyistä yhteensopivuutta possu2 efektien kanssa.

// Jan Äärelä ~ 2026
// ELEKTRONIIKKAKERHO

// Tuodaan muut tiedotot.
#include "kuviot.h"
#include <avr/io.h>
#include <util/delay.h>

// Main funktio
int main(void) {

    // 16MHz PLL asetukset
    // Low fuse = E1
    // CLKPR = (1 << CLKPCE);
    // CLKPR = 0;

    // Tässäpä ne efektit looppaa.
    while (1) {

        // NOTE: Eka parametri kerrrat,
        // Toinen nopeus (montako kertaa vilkuttaa)

        // Testaus kamaa
        // onebyone(1, 20);
        // kirkkaustesti();
        // kaikki(15);

        // Looppaa muut efektit
        for (uint8_t loop = 0; loop < 31; loop++) {
            taytto(2, 1);
            himmennys(2, 7);
            kaks(2, 1);
            alas(2, 2);
            ympari(2, 2);
            kolmiotk(2, 4);
            kolari(2, 1);
            kukka2(2, 3);
        }
    }
}
