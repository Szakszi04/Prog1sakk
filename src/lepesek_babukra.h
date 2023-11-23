#ifndef NAGGYHAZIAMIGNEMLESZMEGJAVULVA_LEPESEK_BABUKRA_H
#define NAGGYHAZIAMIGNEMLESZMEGJAVULVA_LEPESEK_BABUKRA_H

#include <stdbool.h>
#include <stdlib.h>

#include "lepeskisegitofuggvenyek.h"
#include "sakktabla.h"

//gparaszt, bastya, huszar,futo, kiralzno

bool szabalyos_gyalog(int x_innen, int x_oda, int y_innen, int y_oda, Babuk ftabla[8][8]);

bool szabalyos_bastya(int x_innen, int x_oda, int y_innen, int y_oda, Babuk ftabla[8][8]);

bool szabalyos_huszar(int x_innen, int x_oda, int y_innen, int y_oda);

bool szabalyos_futo(int x_innen, int x_oda, int y_innen, int y_oda, Babuk ftabla[8][8]);

bool szabalyos_kiralyno(int x_innen, int x_oda, int y_innen, int y_oda, Babuk ftabla[8][8]);

bool szabalyos_kiraly(int x_innen, int x_oda, int y_innen, int y_oda);

#endif //NAGGYHAZIAMIGNEMLESZMEGJAVULVA_LEPESEK_BABUKRA_H
