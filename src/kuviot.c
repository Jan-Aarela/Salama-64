// vim: foldmethod=marker ft=c

// Tuodaan muut tiedostot.
#include "vilkutus.c"
#include <avr/io.h>
#include <stdint.h>

// Kaikki ledit {{{
void kaikki(uint16_t tila) {
    int i;
    for (i = 0; i <= 63; i++) {
        kirkkaus[i] = tila;
    }
    vilkutus();
} // }}}

// Classic - Himmennys {{{
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

// Viivat {{{
void viivat(uint16_t kerrat, uint8_t nopeus) {
    uint8_t i;
    uint8_t j;
    uint8_t r;
    uint16_t k; // kerrat
    for (k = 0; k < kerrat; k++) {

        // 1. ledijono
        for (i = 0; i <= 23; i++) {
            kirkkaus[i] = 15;
        }
        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }
        for (i = 0; i <= 23; i++) {
            kirkkaus[i] = 0;
        }
        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }

        // 2. ledijono
        for (i = 23; i <= 37; i++) {
            kirkkaus[i] = 15;
        }
        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }
        for (i = 23; i <= 37; i++) {
            kirkkaus[i] = 0;
        }
        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }

        // 3. ledijono
        for (i = 37; i <= 50; i++) {
            kirkkaus[i] = 15;
        }
        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }
        for (i = 37; i <= 50; i++) {
            kirkkaus[i] = 0;
        }
        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }

        // 4. ledijono
        for (i = 50; i <= 63; i++) {
            kirkkaus[i] = 15;
        }
        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }
        for (i = 50; i <= 63; i++) {
            kirkkaus[i] = 0;
        }
        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }
    }
    // Ledien nollaus
    for (i = 50; i <= 63; i++) {
        kirkkaus[i] = 0;
    }
    vilkutus();
}
// }}}

// Kolari {{{
void kolari(uint16_t kerrat, uint8_t nopeus) {
    uint8_t i;
    uint8_t j;
    uint8_t r;
    uint16_t k; // kerrat
    for (k = 0; k < kerrat; k++) {
        for (i = 0; i <= 31; i++) {
            kirkkaus[i] = 15;
            kirkkaus[i + 32] = 15;
            for (j = 0; j <= nopeus; j++) {
                vilkutus();
            }
            for (r = 0; r <= 63; r++) {
                if (kirkkaus[r] == 15) {
                    kirkkaus[r] = 14;
                } else if (kirkkaus[r] == 14) {
                    kirkkaus[r] = 13;
                } else if (kirkkaus[r] == 13) {
                    kirkkaus[r] = 12;
                } else if (kirkkaus[r] == 12) {
                    kirkkaus[r] = 11;
                } else if (kirkkaus[r] == 11) {
                    kirkkaus[r] = 10;
                } else if (kirkkaus[r] == 10) {
                    kirkkaus[r] = 9;
                } else if (kirkkaus[r] == 9) {
                    kirkkaus[r] = 8;
                } else if (kirkkaus[r] == 8) {
                    kirkkaus[r] = 7;
                } else if (kirkkaus[r] == 7) {
                    kirkkaus[r] = 6;
                } else if (kirkkaus[r] == 6) {
                    kirkkaus[r] = 5;
                } else if (kirkkaus[r] == 5) {
                    kirkkaus[r] = 4;
                } else if (kirkkaus[r] == 4) {
                    kirkkaus[r] = 3;
                } else if (kirkkaus[r] == 3) {
                    kirkkaus[r] = 2;
                } else if (kirkkaus[r] == 2) {
                    kirkkaus[r] = 1;
                } else if (kirkkaus[r] == 1) {
                    kirkkaus[r] = 0;
                }
            }
        }
    }
}
// }}}

// kaks {{{
void kaks(uint16_t kerrat, uint8_t nopeus) {
    uint8_t i;
    uint8_t j;
    uint8_t r;
    uint16_t k; // kerrat
    for (k = 0; k < kerrat; k++) {
        for (i = 0; i <= 63; i++) {
            kirkkaus[i] = 15;
            if (i <= 11) {
                kirkkaus[i + 48] = 15;
            } else {
                kirkkaus[i - 16] = 15;
            }
            for (j = 0; j <= nopeus; j++) {
                vilkutus();
            }
            for (r = 0; r <= 63; r++) {
                if (kirkkaus[r] == 15) {
                    kirkkaus[r] = 14;
                } else if (kirkkaus[r] == 14) {
                    kirkkaus[r] = 13;
                } else if (kirkkaus[r] == 13) {
                    kirkkaus[r] = 12;
                } else if (kirkkaus[r] == 12) {
                    kirkkaus[r] = 11;
                } else if (kirkkaus[r] == 11) {
                    kirkkaus[r] = 10;
                } else if (kirkkaus[r] == 10) {
                    kirkkaus[r] = 9;
                } else if (kirkkaus[r] == 9) {
                    kirkkaus[r] = 8;
                } else if (kirkkaus[r] == 8) {
                    kirkkaus[r] = 7;
                } else if (kirkkaus[r] == 7) {
                    kirkkaus[r] = 6;
                } else if (kirkkaus[r] == 6) {
                    kirkkaus[r] = 5;
                } else if (kirkkaus[r] == 5) {
                    kirkkaus[r] = 4;
                } else if (kirkkaus[r] == 4) {
                    kirkkaus[r] = 3;
                } else if (kirkkaus[r] == 3) {
                    kirkkaus[r] = 2;
                } else if (kirkkaus[r] == 2) {
                    kirkkaus[r] = 1;
                } else if (kirkkaus[r] == 1) {
                    kirkkaus[r] = 0;
                }
            }
        }
    }
}
// }}}

// Kolmiot {{{
void kolmiot(uint16_t kerrat, uint8_t nopeus) {
    uint8_t i;
    int8_t w;
    int8_t v;   // vrit
    uint16_t k; // kerrat

    for (k = 0; k < kerrat; k++) {
        for (v = 0, w = 15; v <= 15, w >= 0; v++, w--) {
            for (i = 0; i <= 11; i++) {
                kirkkaus[i] = v;
            }
            for (i = 44; i <= 63; i++) {
                kirkkaus[i] = v;
            }
            for (i = 12; i <= 43; i++) {
                kirkkaus[i] = w;
            }
            for (i = 0; i <= nopeus; i++) {
                vilkutus();
            }
        }

        for (v = 15, w = 0; v >= 0, w <= 15; v--, w++) {
            for (i = 0; i <= 11; i++) {
                kirkkaus[i] = v;
            }
            for (i = 44; i <= 63; i++) {
                kirkkaus[i] = v;
            }
            for (i = 12; i <= 43; i++) {
                kirkkaus[i] = w;
            }

            for (i = 0; i <= nopeus; i++) {
                vilkutus();
            }
        }
    }
    for (i = 0; i <= 63; i++) {
        kirkkaus[i] = 0;
    }
    vilkutus();
}
// }}}

// Strobe {{{
void strobe(uint16_t kerrat, uint8_t nopeus) {
    uint8_t i;
    uint16_t k; // kerrat
    for (k = 0; k < kerrat; k++) {
        for (i = 0; i <= 63; i++) {
            kirkkaus[i] = 15;
        }
        for (i = 0; i <= nopeus; i++) {
            vilkutus();
        }
        for (i = 0; i <= 63; i++) {
            kirkkaus[i] = 13;
        }
        for (i = 0; i <= nopeus; i++) {
            vilkutus();
        }
    }
    for (i = 0; i <= 63; i++) {
        kirkkaus[i] = 0;
    }
    vilkutus();
}
// }}}
