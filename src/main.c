// vim: foldmethod=marker ft=c

// Vanha kunnon possu ISONA.
// Jan Äärelä ~ 2025
// ELEKTRONIIKKAKERHO

// Tuodaan muut tiedotot.
#include "kuviot.c"
#include <avr/io.h>
#include <util/delay.h>

// Main funktio
void main(void) {

    // Delay uudelleen flashäysta varten.
    // _delay_ms(10000);

    // Asetetaan kaikki PA ja PB portit outputiksi.
    //       76543210
    DDRA = 0b11111111;
    DDRB = 0b11111111;

    // Porttien initial state (=low).
    PORTA = 0b00000000;
    PORTB = 0b00000000;

    // Tässäpä ne efektit looppaa.
    while (1) {
        // kaikki(15); // ON
        // _delay_ms(2000);
        // kaikki(0); // OFF
        // _delay_ms(2000);
        onebyone(1, 5);
        taytto(3, 4);
        // himmennys(2, 6); //(kerrat,nopeus)
        // ympari(6,7);
        // aalto(10,1);
    }
}
