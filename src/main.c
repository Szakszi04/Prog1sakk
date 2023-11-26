#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

#include "fajl.h"
#include "grafika.h"
#include "lancolt_lista.h"
#include "lepeskisegitofuggvenyek.h"
#include "sakktabla.h"
#include "debugmalloc.h"

int main(void) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(1000, 1000, &window, &renderer);
    menu(renderer);
    SDL_Point menukatt = menu_kattintas();
    if(menukatt.y != -1) {
        SDL_Texture *babukep, *gomb, *visszagomb;
        int kivansakkban = 10;
        Babuk tabla[8][8];
        FILE *sakkfajl = NULL;
        bool kikov = true, engedelyezes;
        kepbetoltes(renderer, &babukep, &gomb, &visszagomb);
        Lista *volt_lepesek = (Lista *)malloc(sizeof(Lista));
        if (menukatt.y < 500) {// A menüben lévő kattintás alapján eldönti, hogy mi következzené
            feltolt(renderer, babukep, gomb, visszagomb, tabla); // Egy sakk indul alaphelyetből.
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    volt_lepesek->ltabla[i][j].szin = tabla[i][j].szin;
                    volt_lepesek->ltabla[i][j].babu = tabla[i][j].babu;
                }
            }
            volt_lepesek->kov = NULL;

        } else if (fajlbeolvasas(sakkfajl, tabla, &kikov) == 0) { // Egy sakk indul a mentett állapot alapján.
            alaprajz(renderer);
            betoltott_kirajz(renderer, tabla, babukep, gomb, visszagomb);
            elore(&volt_lepesek, tabla);
        }

        do {
            if (!van_sakk(tabla, &kivansakkban)) {
                engedelyezes = true;
                int lepes = megint_sakk(renderer, sakkfajl, babukep, gomb, visszagomb, tabla, &kikov, &volt_lepesek, &kivansakkban, engedelyezes);
                if (lepes == kilepes)
                    break;
                if ((lepes == sakk && (kivansakkban != kikov)) || lepes == nem_sakk) {
                    kikov = !kikov;
                    betoltott_kirajz(renderer, tabla, babukep, gomb, visszagomb);
                    elore(&volt_lepesek, tabla);
                }

            } else if (sakkmatt(tabla, kivansakkban)) {
                break;
            } else if (van_sakk(tabla, &kivansakkban)) {
                engedelyezes = false;
                int masiklepes = megint_sakk(renderer, sakkfajl, babukep, gomb, visszagomb, tabla, &kikov, &volt_lepesek, &kivansakkban, engedelyezes);
                if(masiklepes == kilepes)
                    break;
                while (masiklepes != nem_sakk) {
                    masiklepes = megint_sakk(renderer, sakkfajl, babukep, gomb, visszagomb, tabla, &kikov, &volt_lepesek, &kivansakkban, engedelyezes);
                }
                kikov = !kikov;
                betoltott_kirajz(renderer, tabla, babukep, gomb, visszagomb);
                elore(&volt_lepesek, tabla);
            }


        } while (true);
        felszabadit_elore(volt_lepesek);

    }

    return 0;
}
