#ifndef NAGGYHAZIAMIGNEMLESZMEGJAVULVA_ENUM_H
#define NAGGYHAZIAMIGNEMLESZMEGJAVULVA_ENUM_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>

typedef enum Babukkoddal{
    ures = -1,
    kiraly ,
    kiralyno ,
    bastya ,
    futo,
    huszar ,
    gyalog
} Babukkoddal;

typedef enum Szinek{
    feher = -1,
    nincs ,
    fekete
}Szinek;

typedef struct Babuk{
    Babukkoddal babu ;
    Szinek szin;
}Babuk;

/* a pieces_2.png fajlban levo figurak merete */
enum { MERET = 110};


typedef struct Kepek{
    SDL_Texture *babuk, *gomb, *lista;
}Kepek;




#endif //NAGGYHAZIAMIGNEMLESZMEGJAVULVA_ENUM_H
