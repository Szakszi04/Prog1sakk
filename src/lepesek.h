#ifndef NAGGYHAZIAMIGNEMLESZMEGJAVULVA_LEPESEK_H
#define NAGGYHAZIAMIGNEMLESZMEGJAVULVA_LEPESEK_H
#include "sakktabla.h"
#include <stdbool.h>
#include <stdlib.h>

bool szabalyoslepes(babuk fuggvenybabu,int x_innen,int x_oda,int y_innen , int y_oda){
    bool elsolepes = true;
    int viszgalandomezo;
    switch (fuggvenybabu.babu) {
        case kiraly:
            break;
        case kiralyno:
            break;
        case bastya:
            break;
        case futo:
            break;
        case huszar:
            break;
        case gyalog:
            if(abs(x_innen-x_oda) == 2 && elsolepes && y_innen == y_oda && tabla[x_oda][y_oda].babu == ures)
                fuggvenybabu.szin == 1 ? viszgalandomezo = x_innen+1 : viszgalandomezo = x_innen

            if(abs(x_innen-x_oda) <3 && abs(x_innen-x_oda) >0  && y_innen == y_oda )
                return true;

            break;
        default:
            return true;

    }
    return true;
}

#endif //NAGGYHAZIAMIGNEMLESZMEGJAVULVA_LEPESEK_H
