#ifndef NAGGYHAZIAMIGNEMLESZMEGJAVULVA_SAKKTABLA_H
#define NAGGYHAZIAMIGNEMLESZMEGJAVULVA_SAKKTABLA_H
#include "enum.h"
#include <stdio.h>
babuk tabla[8][8];

void feltolt(void) {
    for (int i = 2; i < 5; ++i) {
        for (int j = 0; j < 8; ++j) {
            tabla[i][j].babu = ures;
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i == 1) {
                tabla[i][j].babu = gyalog;
                tabla[i][j].szin = fekete;


            }
            else if (i == 0) {
                tabla[i][0].babu = bastya, tabla[i][1].babu = huszar, tabla[i][2].babu = futo, tabla[i][3].babu = kiraly, tabla[i][4].babu = kiralyno, tabla[i][5].babu = futo, tabla[i][6].babu = huszar, tabla[i][7].babu = bastya;
                tabla[i][j].szin = fekete;

            }
        }
    }
    for (int i = 6; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i == 6) {
                tabla[i][j].babu = gyalog;
                tabla[i][j].szin = feher;
            } else if (i == 7) {
                tabla[i][0].babu = bastya, tabla[i][1].babu = huszar, tabla[i][2].babu = futo, tabla[i][3].babu = kiraly, tabla[i][4].babu = kiralyno, tabla[i][5].babu = futo, tabla[i][6].babu = huszar, tabla[i][7].babu = bastya;
                tabla[i][j].szin = feher;
            }
        }
    }
}


#endif //NAGGYHAZIAMIGNEMLESZMEGJAVULVA_SAKKTABLA_H
