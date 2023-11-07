#ifndef NAGGYHAZIAMIGNEMLESZMEGJAVULVA_LEPESEK_BABUKRA_H
#define NAGGYHAZIAMIGNEMLESZMEGJAVULVA_LEPESEK_BABUKRA_H
#include <stdbool.h>
#include <stdlib.h>
#include "sakktabla.h"
#include "lepeskisegitofuggvenyek.h"

//gparaszt, bastya, huszar,futo, kiralzno

bool szabalyos_gyalog(babuk fuggveny,int x_innen, int x_oda, int y_innen, int y_oda) {
    if (y_innen == y_oda) {
        if (fuggveny.szin == fekete) {
            if (x_innen < x_oda ) {
                if (abs(x_innen - x_oda) == 1) {
                    return true;
                } else if (abs(x_innen - x_oda) == 2 && x_innen == 1 && nincsakadalylinearisan(x_innen, x_oda, y_innen, y_oda))  { //elsolepes-e
                    return true;
                }
            }
        } else {
            if (x_innen > x_oda) {
                if (abs(x_innen - x_oda) == 1) {
                    return true;
                } else if (abs(x_innen - x_oda) == 2 && x_innen == 6 && nincsakadalylinearisan(x_innen, x_oda, y_innen, y_oda)) { //elsolepes-e
                    return true;
                }
            }
        }
        return false;
    }
}

bool szabalyos_bastya(int x_innen, int x_oda, int y_innen, int y_oda){
    if(y_innen == y_oda) {
        if (nincsakadalylinearisan(x_innen, x_oda, y_innen, y_oda))
            return true;
    }
    else if(x_innen == x_oda)
        if (nincsakadalylinearisan(x_innen, x_oda, y_innen, y_oda))
            return true;
    return false;
}

bool szavalyos_huszar(int x_innen, int x_oda, int y_innen, int y_oda){
    if(abs(x_innen-x_oda) + abs(y_innen-y_oda) == 3)
        return true;
    return false;
}

bool szabalyos_futo(int x_innen, int x_oda, int y_innen, int y_oda){
    if(abs(x_innen-x_oda) == abs(y_innen-y_oda) && nincsakadalykeresztbe(x_innen, x_oda, y_innen, y_oda))
        return true;
    return false;
}
bool szabalyos_kiralyno(int x_innen, int x_oda, int y_innen, int y_oda){
    if(szabalyos_futo(x_innen, x_oda, y_innen,  y_oda))
        return true;
    else if(szabalyos_bastya(x_innen, x_oda, y_innen,  y_oda))
        return true;
    return false;
}



#endif //NAGGYHAZIAMIGNEMLESZMEGJAVULVA_LEPESEK_BABUKRA_H
