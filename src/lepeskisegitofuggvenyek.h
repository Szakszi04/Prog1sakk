
#ifndef NAGGYHAZIAMIGNEMLESZMEGJAVULVA_LEPESKISEGITOFUGGVENYEK_H
#define NAGGYHAZIAMIGNEMLESZMEGJAVULVA_LEPESKISEGITOFUGGVENYEK_H
#include <stdbool.h>
#include "enum.h"
#include "lepesek.h"

typedef struct Kiraly_pozicio{
    int vk_j, vk_i, sk_i, sk_j;
}Kiraly_pozicio;

bool nincsakadalylinearisan(int x_errol,int x_ide,int y_errol, int y_ide, Babuk ftabla[8][8]);


bool nincsakadalykeresztbe(int x_errol,int x_ide,int y_errol, int y_ide,Babuk ftabla[8][8]);
Kiraly_pozicio hol_kiraly(Babuk ftabla[8][8]);
bool van_sakk(Babuk ftabla[8][8], int *kivansakk);
bool sakkmatt(Babuk ftabla[8][8], int kivansakk);

#endif //NAGGYHAZIAMIGNEMLESZMEGJAVULVA_LEPESKISEGITOFUGGVENYEK_H
