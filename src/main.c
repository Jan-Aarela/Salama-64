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
        taytto(3, 0);
        himmennys(2, 3);
        // kaks(3, 1);
        kolmiot(3, 2);
        kolari(5, 0);
        viivat(2, 2);
        viivat(4, 1);
        viivat(6, 0);
        strobe(12, 6);
        // ympari(3, 4);
    }
}
