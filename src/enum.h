#ifndef NAGGYHAZIAMIGNEMLESZMEGJAVULVA_ENUM_H
#define NAGGYHAZIAMIGNEMLESZMEGJAVULVA_ENUM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>

typedef enum Babukkoddal { // A bábuk hivatkozását segiti ez az enum.
    ures = -1,
    kiraly,
    kiralyno,
    bastya,
    futo,
    huszar,
    gyalog
} Babukkoddal;

typedef enum Szinek { //A bábuk hivatkozását segiti ez az enum.
    nincs = -1,
    fekete,
    feher
} Szinek;

typedef struct Babuk { // A 2 enum segitségével, egy stukrurát alkott a bábukra.
    Babukkoddal babu;
    Szinek szin;
} Babuk;

/* a pieces_2.png fajlban levo figurak merete */
enum { MERET = 110 }; // A gombok, beállitását segiti.


#endif //NAGGYHAZIAMIGNEMLESZMEGJAVULVA_ENUM_H
