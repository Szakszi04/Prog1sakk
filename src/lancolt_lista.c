#include "lancolt_lista.h"
#include "debugmalloc.h"

void elore(Lista **u, Babuk ftabla[8][8]) { // A jelenlegi sakk állást elmenti, egy láncolt listában. Ay első elemként.

    Lista *uj = (Lista *)malloc(sizeof(Lista));

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            uj->ltabla[i][j].babu = ftabla[i][j].babu;
            uj->ltabla[i][j].szin = ftabla[i][j].szin;
        }
    }
    uj->kov = *u;
    *u = uj;
}

void felszabadit_elore(Lista *u) { // felszabaditja a dinamikusan foglalt lista elemeit.
    Lista *temp = NULL;
    while (u != NULL) {
        temp = u->kov;
        free(u);
        u = temp;
    }
}

void lepkedes_elore(Lista **u) { //  A kapott lista pointert át állitja az utána levőre, és felszabaditja a paraméterként memória helyét.
    if (*u != NULL && (*u)->kov != NULL) {
        Lista *kov = (*u)->kov;
        free(u);
        *u = kov;
        SDL_Log("Lépkedés előre");
    }
}
