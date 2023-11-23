#include "sakktabla.h"

void feltolt(SDL_Renderer *renderer, SDL_Texture *babukep, SDL_Texture *gomb, SDL_Texture *vissza, Babuk ftabla[8][8]) {
    alaprajz(renderer);
    for (int i = 2; i < 6; ++i) {
        for (int j = 0; j < 8; ++j) {
            ftabla[i][j].babu = ures;
            ftabla[i][j].szin = nincs;
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i == 1) {
                ftabla[i][j].babu = gyalog;
                ftabla[i][j].szin = fekete;
            } else if (i == 0) {
                ftabla[i][0].babu = bastya, ftabla[i][1].babu = huszar, ftabla[i][2].babu = futo, ftabla[i][3].babu = kiraly, ftabla[i][4].babu = kiralyno, ftabla[i][5].babu = futo, ftabla[i][6].babu = huszar, ftabla[i][7].babu = bastya;
                ftabla[i][j].szin = fekete; //adatok betoltese
            }
        }
    }
    for (int i = 6; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i == 6) {
                ftabla[i][j].babu = gyalog;
                ftabla[i][j].szin = feher;
            } else if (i == 7) {
                ftabla[i][0].babu = bastya, ftabla[i][1].babu = huszar, ftabla[i][2].babu = futo, ftabla[i][3].babu = kiraly, ftabla[i][4].babu = kiralyno, ftabla[i][5].babu = futo, ftabla[i][6].babu = huszar, ftabla[i][7].babu = bastya;
                ftabla[i][j].szin = feher;
            }
        }
    }
    betoltott_kirajz(renderer, ftabla, babukep, gomb, vissza);
    SDL_RenderPresent(renderer);
}
