#include <stdbool.h>
#include <stdlib.h>
#include "sakktabla.h"

#ifndef NAGYHAZI_FAJL_H
#define NAGYHAZI_FAJL_H
int fajlkiiras(FILE *fajl, Babuk ftabla[8][8], bool kijon);
int fajlbeolvasas(FILE *fajl, Babuk ftabla[8][8], bool * kijon );

#endif //NAGYHAZI_FAJL_H
