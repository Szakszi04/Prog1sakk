#ifndef NAGGYHAZIAMIGNEMLESZMEGJAVULVA_ENUM_H
#define NAGGYHAZIAMIGNEMLESZMEGJAVULVA_ENUM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>

typedef enum Babukkoddal {
    ures = -1,
    kiraly,
    kiralyno,
    bastya,
    futo,
    huszar,
    gyalog
} Babukkoddal;

typedef enum Szinek {
    feher = -1,
    nincs,
    fekete
} Szinek;

typedef struct Babuk {
    Babukkoddal babu;
    Szinek szin;
} Babuk;

/* a pieces_2.png fajlban levo figurak merete */
enum { MERET = 110 };

typedef struct Kepek {
    SDL_Texture *babuk, *gomb, *lista;
} Kepek;

#endif //NAGGYHAZIAMIGNEMLESZMEGJAVULVA_ENUM_H
