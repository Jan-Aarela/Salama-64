// vim: foldmethod=marker ft=c

// Vanha kunnon possu ISONA.
// Jan Äärelä ~ 2025
// ELEKTRONIIKKAKERHO

// Tuodaan muut tiedostot.
#include "vilkutus.c"
#include <avr/io.h>
#include <stdint.h>

// Muuttujia
// int8_t kirkkaus[64];

// Kaikki ledit {{{
void kaikki(uint16_t tila) {
  int i;
  for (i = 0; i <= 63; i++) {
    kirkkaus[i] = tila;
  }
  vilkutus();
} // }}}

// Himmennys {{{
void himmennys(uint16_t kerrat,
    uint8_t nopeus) //(kerrat = montako kertaa kydn koko kuvio lpi,
                    // nopeus = montako kertaa kutsutaan vilkutusta
                    // ennenkuin vaihdetaan svy)
{
  uint8_t i;
  int8_t v;   // vrit
  uint16_t k; // kerrat
  for (k = 0; k < kerrat; k++) {
    for (v = 0; v <= 15; v++) {
      for (i = 0; i <= 63; i++) {
        kirkkaus[i] = v;
      }
      for (i = 0; i <= nopeus; i++) {
        vilkutus();
      }
    }

    for (v = 15; v >= 0; v--) {
      for (i = 0; i <= 63; i++) {
        kirkkaus[i] = v;
      }
      for (i = 0; i <= nopeus; i++) {
        vilkutus();
      }
    }
  }
}
// }}}

// yks kerrallaan {{{
void onebyone(uint16_t kerrat, uint8_t nopeus) {
  uint8_t i;
  uint8_t n;
  uint16_t k; // kerrat
  for (k = 0; k < kerrat; k++) {
    for (i = 0; i <= 63; i++) {
      kirkkaus[i] = 15;

      for (n = 0; n <= nopeus; n++) {
        vilkutus();
      }

      kirkkaus[i] = 0;
    }
  }
}
// }}}

// Täyttö, kaikki kerrallaan {{{
void taytto(uint16_t kerrat, uint8_t nopeus) {
  uint8_t i;
  uint8_t j;
  uint16_t k; // kerrat
  for (k = 0; k < kerrat; k++) {
    for (i = 0; i <= 63; i++) {
      kirkkaus[i] = 15;
      for (j = 0; j <= nopeus; j++) {
        vilkutus();
      }
    }
    for (i = 0; i <= 63; i++) {
      kirkkaus[i] = 0;
      for (j = 0; j <= nopeus; j++) {
        vilkutus();
      }
    }
  }
}
// }}}
