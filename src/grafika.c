#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "enum.h"
#include "fajl.h"
#include "grafika.h"
#include "lepesek.h"
#include "debugmalloc.h"

void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) { // A grafikai elemek/paramétereknek adja meg az értékét, hogy a többi funkió dolgozni tudjon velük.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("SDL peldaprogram", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }

    *pwindow = window;
    *prenderer = renderer;
}

void alaprajz(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    boxRGBA(renderer, 0, 0, 1000, 1000, 205, 205, 205, 0xFF);
    for (int k = 0, z = 0; k < 4; ++k, z = z + 200) {
        for (int i = 0, j = 0; i < 8; ++i, j = j + 100) {
            if (j % 200 == 0)
                boxRGBA(renderer, 100 + j, 100 + z, 200 + j, 200 + z, 255, 255, 255, 0xFF);
            else
                boxRGBA(renderer, 100 + j, 100 + z, 200 + j, 200 + z, 0, 0, 0, 0xFF);
        }
    }
    for (int k = 0, z = 100; k < 4; ++k, z = z + 200) {
        for (int i = 0, j = 0; i < 8; ++i, j = j + 100) {
            if (j % 200 == 0)
                boxRGBA(renderer, 100 + j, 100 + z, 200 + j, 200 + z, 0, 0, 0, 0xFF);
            else
                boxRGBA(renderer, 100 + j, 100 + z, 200 + j, 200 + z, 255, 255, 255, 0xFF);
        }
    }
    SDL_RenderPresent(renderer);
} // A tábla fekete fehér alapját megrajzolja, és a hátteret.

void kepbetoltes(SDL_Renderer *renderer, SDL_Texture **babukep, SDL_Texture **mentesgomb, SDL_Texture **visszagomb) {
    *babukep = IMG_LoadTexture(renderer, "assets/pieces_2.png");
    if (*babukep == NULL) {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        exit(1);
    }
    *mentesgomb = IMG_LoadTexture(renderer, "assets/gomb.png");
    if (*mentesgomb == NULL) {
        SDL_Log("Nem nyithato meg a gombfajl: %s", IMG_GetError());
        exit(1);
    }
    *visszagomb = IMG_LoadTexture(renderer, "assets/vissza.png");
    if (*mentesgomb == NULL) {
        SDL_Log("Nem nyithato meg a gombfajl: %s", IMG_GetError());
        exit(1);
    }
} // Minden png-t amit késöbb gombként, szeretnék felhasználni. Azoknak a paramétereit adja meg.

void visszagomb_rajz(SDL_Renderer *renderer, SDL_Texture *vissza, int x, int y) {
    SDL_Rect src = {18, 22, 765, 740};
    SDL_Rect dest = {x, y, 83, 75};
    SDL_RenderCopy(renderer, vissza, &src, &dest);
} // A kepbetoltestől kapott, paraméterek alapján a vissza funkciót tartalmazó gombot a jobb felső sarokba rajzolja.

void gombrajz(SDL_Renderer *renderer, SDL_Texture *gomb, int x, int y) {
    SDL_Rect src = {541, 545, 189, 180};
    SDL_Rect dest = {x, y, 83, 75};
    SDL_RenderCopy(renderer, gomb, &src, &dest);
} // A kepbetoltestől kapott, paraméterek alapján a mentés funkciót tartalmazó gombot a jobb also sarokba rajzolja.

void vbabu_rajzol(SDL_Renderer *renderer, SDL_Texture *babukep, Babukkoddal melyik, int x, int y) {
    /* a forras kepbol ezekrol a koordinatakrol, ilyen meretu reszletet masolunk. */
    SDL_Rect src = {21 + (melyik * 99), 26, 86, 86};
    /* a cel kepre, ezekre a koordinatakra masoljuk */
    SDL_Rect dest = {x, y, MERET, MERET};
    /* kepreszlet masolasa */
    SDL_RenderCopy(renderer, babukep, &src, &dest);
} // A kepbetoltestől kapott, paraméterek alapján a fehér babukat képes a kért kodrinátákra rajzolni.

void sbabu_rajzol(SDL_Renderer *renderer, SDL_Texture *babukep, Babukkoddal melyik, int x, int y) {
    /* a forras kepbol ezekrol a koordinatakrol, ilyen meretu reszletet masolunk. */
    SDL_Rect src = {21 + (melyik * 99), 121, 86, 86};
    /* a cel kepre, ezekre a koordinatakra masoljuk */
    SDL_Rect dest = {x, y, MERET, MERET};
    /* kepreszlet masolasa */
    SDL_RenderCopy(renderer, babukep, &src, &dest);
} // A kepbetoltestől kapott, paraméterek alapján a fekete babukat képes a kért kodrinátákra rajzolni.

void menu(SDL_Renderer *renderer) {
    boxRGBA(renderer, 0, 0, 1000, 1000, 23, 75, 218, 0xFF);
    SDL_Color szin = {0, 12, 107,0};
    TTF_Init();
    TTF_Font *szovegtipus = TTF_OpenFont("assets/LiberationSerif-Regular.ttf", 56);
    if (!szovegtipus) {
        SDL_Log("Nem sikerult megnyitni a szovegtipust! %s\n", TTF_GetError());
        exit(1);
    }
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect hova = {0, 0, 0, 0};
    surface = TTF_RenderUTF8_Blended(szovegtipus, "Új játék", szin);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    hova.x = (1000 - surface->w) / 2;
    hova.y = 300;
    hova.w = surface->w;
    hova.h = surface->h;
    SDL_RenderCopy(renderer, texture, NULL, &hova);
    SDL_FreeSurface(surface);
    surface = TTF_RenderUTF8_Blended(szovegtipus, "Játék folytatása", szin);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    hova.x = (1000 - surface->w) / 2;
    hova.y = 550;
    hova.w = surface->w;
    hova.h = surface->h;
    SDL_RenderCopy(renderer, texture, NULL, &hova);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(szovegtipus);
} // A menü oldalt grafikailag összerakja és megjelenet.

SDL_Point kattintas() {
    SDL_Event event;
    SDL_Point kattintaspozicio = {-1, -1};

    while (SDL_WaitEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            break;
        } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && event.button.x >= 100 && event.button.x <= 1000 && event.button.y >= 0 && event.button.y <= 1000) {
            // Bal egérgomb lenyomása
            kattintaspozicio.x = event.button.x / 100 - 1;
            kattintaspozicio.y = event.button.y / 100 - 1;
            break;
        }
    }
    return kattintaspozicio;
} // Az egér kattintás adja vissza, amivel tudnak a függvények tovább dolgozni a sakkban.

SDL_Point menu_kattintas() {
    SDL_Event event;
    SDL_Point kattintaspozicio = {-1, -1};

    while (SDL_WaitEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            break;
            // Kilépés, ha ablakot bezárják

        } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && event.button.x >= 300 && event.button.x <= 700 && ((event.button.y >= 540 && event.button.y <= 640) || (event.button.y >= 300 && event.button.y <= 380))) {
            // Bal egérgomb lenyomása
            kattintaspozicio.x = event.button.x;
            kattintaspozicio.y = event.button.y;
            break;
        }
    }
    return kattintaspozicio;
} // Az egér kattintás adja vissza, amivel tudnak a függvények tovább dolgozni a menüben.

void betoltott_kirajz(SDL_Renderer *renderer, Babuk ftabla[8][8], SDL_Texture *babukep, SDL_Texture *gomb, SDL_Texture *vissza) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (ftabla[i][j].szin == fekete)
                sbabu_rajzol(renderer, babukep, ftabla[i][j].babu, ((j + 1) * 100) + 5, ((i + 1) * 100) + 10);
            else if (ftabla[i][j].szin == feher)
                vbabu_rajzol(renderer, babukep, ftabla[i][j].babu, ((j + 1) * 100) + 5, ((i + 1) * 100) + 10);
            else if (ftabla[i][j].babu == ures) {
                if ((i + j) % 2) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_Rect rect = {(j + 1) * 100, (i + 1) * 100, 100, 100};
                    SDL_RenderFillRect(renderer, &rect);
                } else {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_Rect rect = {(j + 1) * 100, (i + 1) * 100, 100, 100};
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
    }
    visszagomb_rajz(renderer, vissza, 905, 10);
    gombrajz(renderer, gomb, 905, 910);
    SDL_RenderPresent(renderer);
} // A paraméterként kapott sakk állást tudja grafikailag kirajzolnié
