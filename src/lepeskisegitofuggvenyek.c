#include "lepeskisegitofuggvenyek.h"
#include "lepesek.h"
#include "fajl.h"
#include "debugmalloc.h"

bool nincsakadalylinearisan(int x_errol, int x_ide, int y_errol, int y_ide, Babuk ftabla[8][8]) {
    if (y_errol < y_ide) // felfele viszgaljuk
        for (int i = y_errol + 1; i < y_ide; i++) {
            if (ftabla[i][x_ide].babu != ures)
                return false;
        }
    else if (y_errol > y_ide)
        for (int i = y_errol - 1; i > y_ide; i--) {
            if (ftabla[i][x_ide].babu != ures)
                return false;
        }
    else if (x_errol < x_ide)
        for (int i = x_errol + 1; i < x_ide; i++) {
            if (ftabla[y_ide][i].babu != ures)
                return false;
        }
    else
        for (int i = x_errol - 1; i > x_ide; i--) {
            if (ftabla[y_ide][i].babu != ures)
                return false;
        }
    return true;
} // Megviszgálja, hogy van e bábu a bábu és a lépési szándéka között függölegesen és vÍzszintesen.

bool nincsakadalykeresztbe(int x_errol, int x_ide, int y_errol, int y_ide, Babuk ftabla[8][8]) {
    if (y_errol < y_ide) {
        if (x_errol < x_ide) {
            for (int j = x_errol + 1, i = y_errol + 1; j < x_ide; ++j, ++i)
                if (ftabla[i][j].babu != ures)
                    return false;
        } else
            for (int j = x_errol - 1, i = y_errol + 1; j > x_ide; --j, ++i)
                if (ftabla[i][j].babu != ures)
                    return false;
    } else if (x_errol < x_ide) {
        for (int j = x_errol + 1, i = y_errol - 1; j < x_ide; ++j, --i)
            if (ftabla[i][j].babu != ures)
                return false;
    } else
        for (int j = x_errol - 1, i = y_errol - 1; j > x_ide; --j, --i)
            if (ftabla[i][j].babu != ures)
                return false;
    return true;
} // Megviszgálja, hogy van e bábu a bábu és a lépési szándéka között keresztben.

Kiraly_pozicio hol_kiraly(Babuk ftabla[8][8]) {
    Kiraly_pozicio f;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (ftabla[i][j].babu == kiraly) {
                if (ftabla[i][j].szin == fekete) {
                    f.sk_i = i;
                    f.sk_j = j;
                } else {
                    f.vk_i = i;
                    f.vk_j = j;
                }
            }
        }
    }
    return f;
} // Kiraly_pozicio strukturába eltárolja a 2 király pozicioját.

bool van_sakk(Babuk ftabla[8][8], int *kivansakk) {
    Kiraly_pozicio a = hol_kiraly(ftabla);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (ftabla[i][j].babu != ures) {
                if (ftabla[i][j].szin == fekete) {
                    if (szabalyoslepes(j, a.vk_j, i, a.vk_i, ftabla)) {
                        *kivansakk = feher;
                        return true;
                    }

                } else if (szabalyoslepes(j, a.sk_j, i, a.sk_i, ftabla)) {
                    *kivansakk = fekete;
                    return true;
                }
            }
        }
    }
    return false;
} // A jelenlegi tábla állapot alapján megvizsgálja, hogy van-e sakk.

bool sakkmatt(Babuk ftabla[8][8], int kivansakk) {
    Babuk temp;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (ftabla[i][j].babu != ures && ftabla[i][j].szin == kivansakk)
                for (int k = 0; k < 8; ++k) {
                    for (int l = 0; l < 8; ++l) {
                        if (szabalyoslepes(j, l, i, k, ftabla)) {
                            temp.babu = ftabla[k][l].babu;
                            temp.szin = ftabla[k][l].szin;
                            ftabla[k][l] = ftabla[i][j];
                            ftabla[i][j].babu = ures;
                            ftabla[i][j].szin = nincs;
                            if (!van_sakk(ftabla, &kivansakk)) {
                                ftabla[i][j] = ftabla[k][l];
                                ftabla[k][l].babu = temp.babu;
                                ftabla[k][l].szin = temp.szin;
                                return false;
                            }
                            ftabla[i][j] = ftabla[k][l];
                            ftabla[k][l].babu = temp.babu;
                            ftabla[k][l].szin = temp.szin;
                        }
                    }
                }
        }
    }
    return true;
} // Lefuttat egy szimuláciot a sakk függvény segitségével, ami eldönti, hogy sakk matt-e.

int megint_sakk(SDL_Renderer *renderer, FILE *fajl,SDL_Texture *babukep, SDL_Texture *gomb, SDL_Texture *vissza,  Babuk fuggvenytabla[8][8], bool *feher_kov, Lista **u, int *kivansakk, bool engedely) {
    // Leszimulál egy sakk lépést, és utána eldönti, hogy azt a lépést vissza adja-e a mainben lévő mátrix tömbbnek. Ez felel az ütés grafikai szépségéért is.
    int temp_kivansakk;
    Babuk temp[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            temp[i][j] = fuggvenytabla[i][j];
        }
    }
    SDL_Point katthonnan = kattintas();
    if(katthonnan.x == -1)
        return 10;

    if (katthonnan.y == 8 && katthonnan.x == 8) {
        fajlkiiras(fajl, fuggvenytabla, *feher_kov);
        return 0;
    }
    if (katthonnan.y == -1 && katthonnan.x == 8) {
        if (*u == NULL)
            return -1;
        Lista *jelenlegi;
        jelenlegi = lepkedes_elore(*u);
        alaprajz(renderer);
        betoltott_kirajz(renderer, jelenlegi->ltabla, babukep, gomb, vissza);
        *u = jelenlegi;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                fuggvenytabla[i][j] = jelenlegi->ltabla[i][j];
            }
        }
        return -1;
    }
    Szinek kijon;
    kijon = *feher_kov ? fekete : feher;
    if (temp[katthonnan.y][katthonnan.x].babu != ures && temp[katthonnan.y][katthonnan.x].szin != kijon && katthonnan.y < 8 && katthonnan.x < 8 && katthonnan.y > -1) {

        SDL_Point katthova = kattintas();
        if(katthova.y == -1)
            return 10;


        if (szabalyoslepes(katthonnan.x, katthova.x, katthonnan.y, katthova.y, fuggvenytabla) && katthova.y < 8 && katthova.x < 8 && katthova.y > -1) {
            if(temp[katthova.y][katthova.x].babu != ures) {
                    if ((katthova.y + katthova.x) % 2) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_Rect rect = {(katthova.x + 1) * 100, (katthova.y + 1) * 100, 100, 100};
                    SDL_RenderFillRect(renderer, &rect);
                } else {
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        SDL_Rect rect = {(katthova.x + 1) * 100, (katthova.y + 1) * 100, 100, 100};
                        SDL_RenderFillRect(renderer, &rect);
                    }
            }


            temp[katthova.y][katthova.x] = temp[katthonnan.y][katthonnan.x];
            temp[katthonnan.y][katthonnan.x].babu = ures;
            int kileszsakk;
            if(van_sakk(temp,&kileszsakk))
                if(kileszsakk == temp[katthonnan.y][katthonnan.x].szin)
                    return 1;


            if (temp[katthova.y][katthova.x].babu == gyalog && ((temp[katthova.y][katthova.x].szin == feher && katthova.y == 0) ||
                                                                (katthova.y == 7 && temp[katthova.y][katthova.x].szin == fekete)))
                temp[katthova.y][katthova.x].babu = kiralyno;

            temp[katthonnan.y][katthonnan.x].szin = nincs;
            if (van_sakk(temp, &temp_kivansakk)) {
                *kivansakk = temp_kivansakk;
                if (engedely) {
                    for (int i = 0; i < 8; ++i) {
                        for (int j = 0; j < 8; ++j) {
                            fuggvenytabla[i][j] = temp[i][j];
                        }
                    }
                }
                    return 1;
                } else{
                    for (int i = 0; i < 8; ++i) {
                        for (int j = 0; j < 8; ++j) {
                        fuggvenytabla[i][j] = temp[i][j];
                            }
                        }
                return -1;
                }
            }
    }
    return 0;
} //

