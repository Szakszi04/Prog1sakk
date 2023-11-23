#include "lepesek_babukra.h"


bool szabalyos_gyalog(int x_innen, int x_oda, int y_innen, int y_oda,Babuk ftabla[8][8]) {
    if (ftabla[y_innen][x_innen].szin == fekete) {
        if ( x_innen == x_oda && ftabla[y_oda][x_oda].babu == ures) {
            if (y_innen - y_oda == -1)
                return true;
            else return y_innen - y_oda == -2 && y_innen == 1 &&
                     nincsakadalylinearisan(x_innen, x_oda, y_innen, y_oda, ftabla) ; //elsolepes-e
        }
        else
            return abs(x_innen - x_oda) == 1 && y_innen - y_oda == -1 && ftabla[y_oda][x_oda].babu != ures;

    }
    else if( x_innen == x_oda && ftabla[y_oda][x_oda].babu == ures) {
        if (y_innen - y_oda == 1)
            return true;
        else
            return y_innen - y_oda == 2 && y_innen == 6 &&
                   nincsakadalylinearisan(x_innen, x_oda, y_innen, y_oda, ftabla); //elsolepes-e
    }
    else return abs(x_innen-x_oda)==1 && y_innen-y_oda == 1 && ftabla[y_oda][x_oda].babu != ures;

}

bool szabalyos_bastya(int x_innen, int x_oda, int y_innen, int y_oda,Babuk ftabla[8][8]){
    if(x_innen == x_oda || y_innen == y_oda)
        return nincsakadalylinearisan(x_innen, x_oda, y_innen, y_oda,ftabla);

    return false;
}

bool szabalyos_huszar(int x_innen, int x_oda, int y_innen, int y_oda){
    return (x_innen-x_oda)*(x_innen-x_oda) + (y_innen-y_oda)*(y_innen-y_oda) == 5;
}

bool szabalyos_futo(int x_innen, int x_oda, int y_innen, int y_oda,Babuk ftabla[8][8]){
    return abs(x_innen-x_oda) == abs(y_innen-y_oda) && nincsakadalykeresztbe(x_innen, x_oda, y_innen, y_oda,ftabla);
}
bool szabalyos_kiralyno(int x_innen, int x_oda, int y_innen, int y_oda,Babuk ftabla[8][8]){
    return szabalyos_futo(x_innen, x_oda, y_innen,  y_oda,ftabla) || szabalyos_bastya(x_innen, x_oda, y_innen,  y_oda,ftabla);
}
bool szabalyos_kiraly(int x_innen, int x_oda, int y_innen, int y_oda){
    return (abs(x_innen-x_oda)==1 && y_innen==y_oda) || (abs(y_innen-y_oda) ==1 && x_oda == x_innen) ||((abs(y_innen-y_oda) == abs(x_oda - x_innen)&& abs(y_innen-y_oda)==1));
}
