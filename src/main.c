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

    // Tässäpä ne efektit looppaa.
    while (1) {
        // onebyone(1, 4);
        // kaks(3, 1);
        // ympari(3, 4);
        // alas(2, 2);
        // taytto(3, 0);
        kaikki(15);
        // himmennys(2, 3);
        // kolmiotk(3, 2);
        // kolari(5, 0);
        // viivatk(2, 2);
        // viivatk(4, 1);
        // viivatk(6, 0);
        // strobe(12, 6);
    }
}
