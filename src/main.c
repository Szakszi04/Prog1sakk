#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

#include "fajl.h"
#include "grafika.h"
#include "lancolt_lista.h"
#include "lepeskisegitofuggvenyek.h"
#include "sakktabla.h"

int main(void) {
    int kivansakkban;
    int vissza_lepes_db = 1;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *babukep, *gomb, *visszagomb;
    Babuk tabla[8][8];
    sdl_init(1000, 1000, &window, &renderer);
    FILE *sakkfajl = NULL;
    Lista *volt_lepesek = (Lista *)malloc(sizeof(Lista));
    bool kikov = true;
    kepbetoltes(renderer, &babukep, &gomb, &visszagomb);
    menu(renderer);
    int vissszateres_ertek;
    if (menu_kattintas(renderer).y < 500) {
        feltolt(renderer, babukep, gomb, visszagomb, tabla);
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                volt_lepesek->ltabla[i][j].szin = tabla[i][j].szin;
                volt_lepesek->ltabla[i][j].babu = tabla[i][j].babu;
            }
        }
        volt_lepesek->kov = NULL;

        do {
            vissszateres_ertek = grafikailepes(renderer, babukep, gomb, visszagomb, sakkfajl, tabla, &kikov, &volt_lepesek);

            if (van_sakk(tabla, &kivansakkban)) {
                printf("sakk");
                if (sakkmatt(tabla, kivansakkban))
                    alaprajz(renderer);
            }
            if (vissszateres_ertek == 0)
                elore(&volt_lepesek, tabla);
        } while (vissszateres_ertek == 0 || vissszateres_ertek == 1);

    } else if (fajlbeolvasas(sakkfajl, tabla, &kikov) == 0) {
        alaprajz(renderer);
        betoltott_kirajz(renderer, tabla, babukep, gomb, visszagomb);
        do {
            vissszateres_ertek = grafikailepes(renderer, babukep, gomb, visszagomb, sakkfajl, tabla, &kikov, &volt_lepesek);
            if (vissszateres_ertek == 0)
                elore(&volt_lepesek, tabla);
        } while (vissszateres_ertek == 0 || vissszateres_ertek == 1);
    }
    return 0;
}
