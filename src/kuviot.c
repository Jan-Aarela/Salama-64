// vim: foldmethod=marker ft=c

// Tuodaan muut tiedostot.
#include "kuviot.h"
#include "vilkutus_charlie.h"
#include <stdint.h>

int8_t kirkkaus[64] = { 0 };

// Kaikki ledit {{{
void kaikki(uint16_t tila) {
    int i;
    for (i = 0; i <= 63; i++) {
        kirkkaus[i] = tila;
    }
    vilkutus();
} // }}}

// Kirkkaustesti{{{
void kirkkaustesti() {
    int i;
    for (i = 0; i <= 15; i++) {
        kirkkaus[i] = i;
    }
    kirkkaus[16] = 15;
    vilkutus();
    return;
}
// }}}

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

// Classic - Ympäri {{{
void ympari(uint8_t kerrat, uint8_t nopeus) {

    uint8_t k = 0;
    volatile uint8_t j = 0; // miss mennn yhdess framessa
    uint8_t t = 0;          // countteri kunnes pysytett
    int8_t i = 0;
    uint8_t g = 0;
    uint16_t ctr = 64;
    int8_t x = 0;

    // itse kuvio looppi
    for (x = 0; x < kerrat; x++) {
        while (t < ctr) {
            g = nopeus;
            while (g > 0) {
                g--;
                k = 0;
                for (i = 0; i < 16; i++) {
                    if (k + j > 63)
                        kirkkaus[k + j - 64] = i;
                    else
                        kirkkaus[k + j] = i;
                    k++;
                }
                for (i = 15; i > 0; i--) {
                    if (k + j > 63)
                        kirkkaus[k + j - 64] = i;
                    else
                        kirkkaus[k + j] = i;
                    k++;
                }
                vilkutus();
            }
            j++;
            if (j > 63)
                j = 0;
            t++;
        }
        t = 0;
    }
    for (i = 0; i <= 63; i++) {
        kirkkaus[i] = 0;
    }
    vilkutus();
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

// Tyhjennys, kaikki kerrallaan {{{
void tyhjennys(uint8_t nopeus) {
    uint8_t i;
    uint8_t j;

    for (i = 0; i <= 63; i++) {
        kirkkaus[i] = 0;

        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }
    }
}
// }}}

// Viivat {{{
void viivat(uint16_t kerrat, uint8_t nopeus) {
    uint8_t i;
    uint8_t j;
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

// Viivatk {{{
void viivatk(uint16_t kerrat, uint8_t nopeus) {
    uint8_t i;
    uint8_t j;
    uint16_t k; // kerrat
    for (k = 0; k < kerrat; k++) {

        // 1. ledijono
        for (i = 0; i <= 25; i++) {
            kirkkaus[i] = 15;
        }
        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }
        for (i = 0; i <= 25; i++) {
            kirkkaus[i] = 0;
        }
        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }

        // 2. ledijono
        for (i = 25; i <= 39; i++) {
            kirkkaus[i] = 15;
        }
        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }
        for (i = 25; i <= 39; i++) {
            kirkkaus[i] = 0;
        }
        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }

        // 3. ledijono
        for (i = 39; i <= 50; i++) {
            kirkkaus[i] = 15;
        }
        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }
        for (i = 39; i <= 50; i++) {
            kirkkaus[i] = 0;
        }
        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }

        // 4. ledijono
        for (i = 50; i <= 63; i++) {
            kirkkaus[i] = 15;
            kirkkaus[0] = 15;
        }
        for (j = 0; j <= nopeus; j++) {
            vilkutus();
        }
        for (i = 50; i <= 63; i++) {
            kirkkaus[i] = 0;
            kirkkaus[0] = 0;
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
    uint16_t k; // kerrat
    for (k = 0; k < kerrat; k++) {
        for (i = 0; i <= 31; i++) {
            kirkkaus[i] = 15;
            kirkkaus[i + 32] = 15;
            for (j = 0; j <= nopeus; j++) {
                vilkutus();
            }
            for (int r = 0; r <= 63; r++) {
                if (kirkkaus[r] > 0) {
                    kirkkaus[r]--;
                }
            }
        }
    }
    for (i = 0; i <= 63; i++) {
        kirkkaus[i] = 0;
    }
    vilkutus();
}
// }}}

// kaks {{{
void kaks(uint16_t kerrat, uint8_t nopeus) {
    uint8_t i;
    uint8_t j;
    uint16_t k; // kerrat
    for (k = 0; k < kerrat; k++) {
        for (i = 0; i <= 63; i++) {
            kirkkaus[i] = 15;
            if (i <= 40) {
                kirkkaus[i + 23] = 15;
            }
            else {
                kirkkaus[i - 41] = 15;
            }
            for (j = 0; j <= nopeus; j++) {
                vilkutus();
            }
            for (int r = 0; r <= 63; r++) {
                if (kirkkaus[r] > 0) {
                    kirkkaus[r]--;
                }
            }
        }
    }
    for (i = 0; i <= 63; i++) {
        kirkkaus[i] = 0;
    }
    vilkutus();
}
// }}}

// Kolmiot {{{
void kolmiot(uint16_t kerrat, uint8_t nopeus) {
    uint8_t i;
    int8_t w;
    int8_t v;   // vrit
    uint16_t k; // kerrat

    for (k = 0; k < kerrat; k++) {
        for (v = 0, w = 15; w >= 0; v++, w--) {
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

        for (v = 15, w = 0; w <= 15; v--, w++) {
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

// Kolmiotk {{{
void kolmiotk(uint16_t kerrat, uint8_t nopeus) {
    uint8_t i;
    int8_t w;
    int8_t v;   // vrit
    uint16_t k; // kerrat

    for (k = 0; k < kerrat; k++) {
        for (v = 0, w = 15; w >= 0; v++, w--) {
            for (i = 0; i <= 12; i++) {
                kirkkaus[i] = v;
            }
            for (i = 45; i <= 63; i++) {
                kirkkaus[i] = v;
            }
            for (i = 13; i <= 44; i++) {
                kirkkaus[i] = w;
            }

            for (i = 0; i <= nopeus; i++) {
                vilkutus();
            }
        }

        for (v = 15, w = 0; w <= 15; v--, w++) {
            for (i = 0; i <= 12; i++) {
                kirkkaus[i] = v;
            }
            for (i = 45; i <= 63; i++) {
                kirkkaus[i] = v;
            }
            for (i = 13; i <= 44; i++) {
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

// Alas {{{
void alas(uint16_t kerrat, uint8_t nopeus) {
    uint8_t i;
    uint8_t j;
    uint16_t k; // kerrat
    for (k = 0; k < kerrat; k++) {
        for (i = 0; i <= 31; i++) {
            if (i < 13) {
                kirkkaus[i] = 15;
            }
            if (i >= 13) {
                kirkkaus[57 - i] = 15;
            }

            if (i >= 13) {
                kirkkaus[76 - i] = 15;
            }

            if (i < 13) {
                kirkkaus[13 + i] = 15;
            }

            for (j = 0; j <= nopeus; j++) {
                vilkutus();
            }
            for (int r = 0; r <= 63; r++) {
                if (kirkkaus[r] > 0) {
                    kirkkaus[r]--;
                }
            }
        }
    }
    for (i = 0; i <= 63; i++) {
        kirkkaus[i] = 0;
    }
    vilkutus();
}
// }}}

// Vaskakkain{{{
void vastakkain(uint16_t kerrat, uint8_t nopeus) {
    uint8_t i;
    uint8_t j;
    uint16_t k; // kerrat
    for (k = 0; k < kerrat; k++) {
        for (i = 0; i <= 31; i++) {
            if (i <= 31) {
                kirkkaus[i] = 15;
                kirkkaus[63 - i] = 15;
            }
            for (j = 0; j <= nopeus; j++) {
                vilkutus();
            }
            for (int j = 0; j <= 63; j++) {
                if (kirkkaus[j] > 0) {
                    kirkkaus[j]--;
                }
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
            kirkkaus[i] = 12;
        }
        for (i = 0; i <= nopeus; i++) {
            vilkutus();
        }
    }
}
// }}}

// Kukka {{{
void kukka(uint16_t kerrat, uint8_t nopeus) {
    int8_t v;
    int8_t w;
    int8_t i;

    uint16_t k; // kerrat
    for (k = 0; k < kerrat; k++) {

        w = 13;
        for (v = 12; v >= 0; v--) {
            // Pysty
            kirkkaus[v] = 15;
            // Sivu
            kirkkaus[v + 32] = 15;

            // Pysty
            kirkkaus[w] = 15;
            // Sivu
            kirkkaus[w + 32] = 15;

            for (i = 0; i <= nopeus; i++) {
                vilkutus();
            }

            w++;

            for (int r = 0; r <= 63; r++) {
                if (kirkkaus[r] > 0) {
                    kirkkaus[r]--;
                }
            }
        }
        for (v = 0; v <= 6; v++) {

            // Ala
            kirkkaus[31 - v] = 15;
            // Ylä
            if (v == 6) {
                kirkkaus[0] = 15;
            }
            else {
                kirkkaus[58 + v] = 15;
            }

            for (i = 0; i <= nopeus; i++) {
                vilkutus();
            }

            w++;

            for (int r = 0; r <= 63; r++) {
                if (kirkkaus[r] > 0) {
                    kirkkaus[r]--;
                }
            }
        }
        w = 0;
    }
    for (i = 0; i <= 63; i++) {
        kirkkaus[i] = 0;
    }
    vilkutus();

} // }

// Kukka {{{
void kukka2(uint16_t kerrat, uint8_t nopeus) {
    int8_t i;
    int8_t v;
    uint16_t k; // kerrat

    for (k = 0; k < kerrat; k++) {

        for (v = 0; v <= 19; v++) {
            if (v <= 18) {
                kirkkaus[45 + v] = 15;
                kirkkaus[44 - v] = 15;
            }

            if (v >= 7) {
                kirkkaus[6 + v] = 15;
                kirkkaus[19 - v] = 15;
            }

            for (i = 0; i <= nopeus; i++) {
                vilkutus();
            }

            for (int r = 0; r <= 63; r++) {
                if (kirkkaus[r] > 0) {
                    kirkkaus[r]--;
                }
            }
        }
    }
    for (i = 0; i <= 63; i++) {
        kirkkaus[i] = 0;
    }
    vilkutus();

} // }
