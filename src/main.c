// vim: foldmethod=marker ft=c

// Teinpäs possumerkistä xl-mallin (lisäefekteillä).
// Toiminta periaate sama kuin possumerkissä.
// Reset pinni ajettu IO pinniksi fuse asetuksella.

// Jan Äärelä ~ 2026
// ELEKTRONIIKKAKERHO

// Tuodaan muut tiedotot.
#include "kuviot.c"
#include <avr/io.h>
#include <util/delay.h>

// Main funktio
void main(void) {

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

        // taytto(3, 1);
        // kolari(6, 1);
        // himmennys(2, 7);
        // kolmiotk(4, 4);
        // alas(8, 2);

        // Testaus kamaa
        // onebyone(1, 4);
        // kirkkaustesti();
        // kaikki(1);

        // Strobo alku
        viivatk(2, 31);
        viivatk(4, 15);
        viivatk(8, 7);
        viivatk(8, 5);
        viivatk(18, 2);
        viivatk(32, 0);

        strobe(24, 11);
        tyhjennys(1);

        // Looppaa muut efektit
        for (loop = 0; loop < 32; loop++) {
            taytto(12, 1);
            himmennys(12, 7);
            kaks(24, 1);
            // vastakkain(4, 2);
            ympari(24, 2);
            kolmiotk(12, 4);
            kolari(24, 1);
            alas(24, 2);
        }
    }
}
