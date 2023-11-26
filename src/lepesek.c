
#include "lepesek_babukra.h"
#include "debugmalloc.h"

bool szabalyoslepes(int x_innen, int x_oda, int y_innen, int y_oda, Babuk ftabla[8][8]) { // megvizsgálja, hogy a bábu ellép e, és ahova lép ott nem ""csapattárs"" áll.
    if (abs(x_innen - x_oda) + abs(y_innen - y_oda) != 0 && ftabla[y_innen][x_innen].szin != ftabla[y_oda][x_oda].szin) { // Aztán egy switch case segitségével megviszgállja, hogy szabályos-e a lépés.
        switch (ftabla[y_innen][x_innen].babu) {
            case kiraly:
                return szabalyos_kiraly(x_innen, x_oda, y_innen, y_oda);
            case kiralyno:
                return szabalyos_kiralyno(x_innen, x_oda, y_innen, y_oda, ftabla);
            case bastya:
                return szabalyos_bastya(x_innen, x_oda, y_innen, y_oda, ftabla);
            case futo:
                return szabalyos_futo(x_innen, x_oda, y_innen, y_oda, ftabla);
            case huszar:
                return szabalyos_huszar(x_innen, x_oda, y_innen, y_oda);
            case gyalog:
                return szabalyos_gyalog(x_innen, x_oda, y_innen, y_oda, ftabla);
            default:
                return false;
        }
    }
    return false;
}
