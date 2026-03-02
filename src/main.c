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

        // Testaus kamaa
        // onebyone(1, 4);
        // kirkkaustesti();
        // kaikki(15);

        // Strobo alku
        viivatk(3, 10);
        viivatk(4, 6);
        viivatk(7, 2);
        viivatk(14, 0);
        strobe(24, 11);
        tyhjennys(1);

        // Looppaa muut efektit
        for (loop = 0; loop < 7; loop++) {
            taytto(3, 1);
            himmennys(2, 7);
            kaks(4, 1);
            // vastakkain(4, 2);
            ympari(4, 2);
            kolmiotk(4, 4);
            kolari(6, 1);
            alas(12, 0);
        }
    }
}
