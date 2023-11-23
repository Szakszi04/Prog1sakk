#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <SDL_ttf.h>
#include "enum.h"
#include "grafika.h"
#include "lepesek.h"
#include "fajl.h"




void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer){
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window  = SDL_CreateWindow("SDL peldaprogram", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
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
    SDL_Texture *babuk = IMG_LoadTexture(renderer, "/home/adam/CLionProjects/nagyhazi/pieces_2.png");
    if (babuk == NULL) {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        exit(1);
    }
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
}
void kepbetoltes(SDL_Renderer *renderer,SDL_Texture **babukep,SDL_Texture **mentesgomb, SDL_Texture **visszagomb){
    *babukep = IMG_LoadTexture(renderer, "/home/adam/CLionProjects/nagyhazi/pieces_2.png");
    if (*babukep == NULL) {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        exit(1);
    }
    *mentesgomb = IMG_LoadTexture(renderer, "/home/adam/CLionProjects/nagyhazi/gomb.png");
    if (*mentesgomb == NULL) {
        SDL_Log("Nem nyithato meg a gombfajl: %s", IMG_GetError());
        exit(1);
    }
    *visszagomb = IMG_LoadTexture(renderer, "/home/adam/CLionProjects/nagyhazi/vissza.png");
    if (*mentesgomb == NULL) {
        SDL_Log("Nem nyithato meg a gombfajl: %s", IMG_GetError());
        exit(1);
    }
}

void visszagomb_rajz(SDL_Renderer *renderer, SDL_Texture *vissza, int x, int y){
    SDL_Rect src = {18,22,765,740};
    SDL_Rect dest = {x,y,83,75};
    SDL_RenderCopy(renderer, vissza, &src, &dest);

}


void gombrajz(SDL_Renderer *renderer, SDL_Texture *gomb, int x, int y){
    SDL_Rect src = {541,545,189,180};
    SDL_Rect dest = {x,y,83,75};
    SDL_RenderCopy(renderer, gomb, &src, &dest);

}

void vbabu_rajzol(SDL_Renderer *renderer, SDL_Texture *babukep, Babukkoddal melyik, int x, int y) {
    /* a forras kepbol ezekrol a koordinatakrol, ilyen meretu reszletet masolunk. */
    SDL_Rect src = { 21+(melyik*99), 26, 86, 86 };
    /* a cel kepre, ezekre a koordinatakra masoljuk */
    SDL_Rect dest = { x, y, MERET, MERET };
    /* kepreszlet masolasa */
    SDL_RenderCopy(renderer, babukep, &src, &dest);
}


void sbabu_rajzol(SDL_Renderer *renderer, SDL_Texture *babukep, Babukkoddal melyik, int x, int y) {
    /* a forras kepbol ezekrol a koordinatakrol, ilyen meretu reszletet masolunk. */
    SDL_Rect src = { 21+(melyik*99), 121, 86, 86 };
    /* a cel kepre, ezekre a koordinatakra masoljuk */
    SDL_Rect dest = { x, y, MERET, MERET };
    /* kepreszlet masolasa */
    SDL_RenderCopy(renderer, babukep, &src, &dest);

}



void menu(SDL_Renderer *renderer) {
    boxRGBA(renderer, 0, 0, 1000, 1000, 23, 75, 218, 0xFF);
    SDL_Color szin = {0, 12, 107};
    TTF_Init();
    TTF_Font *szovegtipus = TTF_OpenFont("/home/adam/CLionProjects/nagyhazi/LiberationSerif-Regular.ttf", 56);
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

    surface = TTF_RenderUTF8_Blended(szovegtipus, "Játék folytatása", szin );
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    hova.x = (1000 - surface->w) / 2;
    hova.y = 550;
    hova.w = surface->w;
    hova.h = surface->h;
    SDL_RenderCopy(renderer, texture, NULL, &hova);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

}

SDL_Point kattintas(SDL_Renderer *renderer,Lista *u) {
    SDL_Event event;
    SDL_Point kattintaspozicio = {-1, -1};

    while (SDL_WaitEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            felszabadit_elore(u);
            // Kilépés, ha ablakot bezárják
            exit(0);
        } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && event.button.x >=100 && event.button.x <= 1000 && event.button.y >=0 && event.button.y <= 1000  ) {
            // Bal egérgomb lenyomása
            kattintaspozicio.x = event.button.x/100-1;
            kattintaspozicio.y = event.button.y/100-1;
            return kattintaspozicio;
        }
    }

}

SDL_Point menu_kattintas(SDL_Renderer *renderer){
    SDL_Event event;
    SDL_Point kattintaspozicio = {-1, -1};

    while (SDL_WaitEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            // Kilépés, ha ablakot bezárják
            exit(0);
        } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && event.button.x >=300 && event.button.x <= 700 && ((event.button.y >=540 && event.button.y <= 640) || (event.button.y >=300 && event.button.y <= 380))) {
            // Bal egérgomb lenyomása
            kattintaspozicio.x = event.button.x;
            kattintaspozicio.y = event.button.y;
            return kattintaspozicio;
        }
    }


}

int grafikailepes(SDL_Renderer *renderer,SDL_Texture *babukep, SDL_Texture *gomb,SDL_Texture *vissza,FILE *fajl, Babuk fuggvenytabla[8][8], bool *feher_kov, Lista **u){
    SDL_Point katthonnan = kattintas(renderer,*u);
    if(katthonnan.y == 8 && katthonnan.x == 8) {
        fajlkiiras(fajl, fuggvenytabla, *feher_kov);
        return 1;
    }
    if(katthonnan.y == -1 && katthonnan.x == 8) {
        if (*u == NULL)
            return 1;
        Lista *jelenlegi;
        jelenlegi = lepkedes_elore(*u);
        alaprajz(renderer);
        betoltott_kirajz(renderer, jelenlegi->ltabla, babukep, gomb, vissza);
        *u = jelenlegi;
        *feher_kov = !*feher_kov;
        for (int i = 0; i <8 ; ++i) {
            for (int j = 0; j < 8; ++j) {
                fuggvenytabla[i][j].babu = jelenlegi->ltabla[i][j].babu;
                fuggvenytabla[i][j].szin = jelenlegi->ltabla[i][j].szin;
            }
        }
        return 1;
    }
    Szinek kijon;
    kijon = *feher_kov ?  fekete : feher;
        if(fuggvenytabla[katthonnan.y][katthonnan.x].babu != ures && fuggvenytabla[katthonnan.y][katthonnan.x].szin != kijon  && katthonnan.y< 8 && katthonnan.x < 8 && katthonnan.y > -1) {

            SDL_Point katthova = kattintas(renderer,*u);


            if (szabalyoslepes(katthonnan.x, katthova.x, katthonnan.y, katthova.y, fuggvenytabla)  && katthova.y< 8 && katthova.x < 8 && katthova.y > -1) {
                if(fuggvenytabla[katthova.y][katthova.x].babu != ures)
                    kiszinez(renderer, katthova, (katthova.x + katthova.y) % 2 == 0);

                fuggvenytabla[katthova.y][katthova.x].babu = fuggvenytabla[katthonnan.y][katthonnan.x].babu;
                fuggvenytabla[katthova.y][katthova.x].szin = fuggvenytabla[katthonnan.y][katthonnan.x].szin;
                fuggvenytabla[katthonnan.y][katthonnan.x].babu = ures;
                *feher_kov = !*feher_kov;

                if(fuggvenytabla[katthova.y][katthova.x].babu == gyalog && ((fuggvenytabla[katthova.y][katthova.x].szin == feher && katthova.y == 0 )||
                        (katthova.y == 7 && fuggvenytabla[katthova.y][katthova.x].szin == fekete )))
                    fuggvenytabla[katthova.y][katthova.x].babu = kiralyno;

                if (fuggvenytabla[katthonnan.y][katthonnan.x].szin == feher)
                    vbabu_rajzol(renderer, babukep, fuggvenytabla[katthova.y][katthova.x].babu, ((katthova.x + 1) * 100)+5,
                                 ((katthova.y + 1) * 100)+10);

                else
                    sbabu_rajzol(renderer, babukep, fuggvenytabla[katthova.y][katthova.x].babu, ((katthova.x + 1) * 100)+5,
                                 ((katthova.y + 1) * 100)+10);

                fuggvenytabla[katthonnan.y][katthonnan.x].szin=nincs;
                kiszinez(renderer,katthonnan,(katthonnan.x + katthonnan.y) % 2 == 0);
            }
        }
    SDL_RenderPresent(renderer);
    return 0;
}


void betoltott_kirajz(SDL_Renderer *renderer, Babuk ftabla[8][8],SDL_Texture *babukep ,SDL_Texture *gomb, SDL_Texture *vissza){
    for(int i =0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            if(ftabla[i][j].szin == fekete)
                sbabu_rajzol(renderer,babukep,ftabla[i][j].babu,((j+1)*100)+5, ((i+1)*100)+10);
            else
                vbabu_rajzol(renderer,babukep,ftabla[i][j].babu,((j+1)*100)+5, ((i+1)*100)+10);
        }
    }
    visszagomb_rajz(renderer,vissza,905,10);
    gombrajz(renderer,gomb, 905,910);
    SDL_RenderPresent(renderer);
}


void kiszinez(SDL_Renderer *renderer,SDL_Point katt, bool fekete){
     if(fekete) {
         SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
         SDL_Rect rect = {(katt.x + 1) * 100, (katt.y + 1) * 100, 100, 100};
         SDL_RenderFillRect(renderer, &rect);
     }
     else{
         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect rect = {(katt.x + 1) * 100, (katt.y + 1) * 100, 100, 100};
        SDL_RenderFillRect(renderer, &rect);
    }
}
