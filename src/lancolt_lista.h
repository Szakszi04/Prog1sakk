
#ifndef NAGYHAZI_LANCOLT_LISTA_H
#define NAGYHAZI_LANCOLT_LISTA_H

#include <stdlib.h>

#include "enum.h"

typedef struct Lista {
    Babuk ltabla[8][8];
    struct Lista *kov;
} Lista;

void elore(Lista **u, Babuk ftabla[8][8]);

void lepkedes_elore(Lista **u);

void felszabadit_elore(Lista *u);

#endif //NAGYHAZI_LANCOLT_LISTA_H
