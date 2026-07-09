// vim: foldmethod=marker ft=c

// Teinpäs possumerkistä xl-mallin (lisäefekteillä).
// Toiminta periaate sama kuin possumerkissä.
// Reset pinni ajettu IO pinniksi fuse asetuksella.

// Jan Äärelä ~ 2026
// ELEKTRONIIKKAKERHO

// Tuodaan muut tiedotot.
#include "kuviot.h"
#include <avr/io.h>
#include <util/delay.h>

// Main funktio
int main(void) {

    // 16MHz PLL asetukset
    // CLKPR = (1 << CLKPCE);
    // CLKPR = 0;

    // Asetetaan kaikki PA ja PB portit outputiksi.
    //       76543210
    DDRA = 0b11111111;
    DDRB = 0b11111111;

    // Porttien initial state (=low).
    PORTA = 0b00000000;
    PORTB = 0b00000000;

    uint8_t loop;

    // Tässäpä ne efektit looppaa.
    while (1) {

        // Testaus kamaa
        // onebyone(1, 20);
        // kirkkaustesti();
        // kaikki(15);

        // Looppaa muut efektit
        for (loop = 0; loop < 31; loop++) {
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
