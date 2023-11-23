#include "lepeskisegitofuggvenyek.h"


bool nincsakadalylinearisan(int x_errol,int x_ide,int y_errol, int y_ide, Babuk ftabla[8][8]) {
    if (y_errol < y_ide) // felfele viszgaljuk
        for (int i = y_errol + 1; i < y_ide; i++) {
            if (ftabla[i][x_ide].babu != ures)
                return false;
        }
    else if (y_errol > y_ide)
        for (int i = y_errol - 1; i > y_ide; i--) {
            if (ftabla[i][x_ide].babu != ures)
                return false;
        }
    else if (x_errol < x_ide)
        for (int i = x_errol + 1; i < x_ide; i++) {
            if (ftabla[y_ide][i].babu != ures)
                return false;
        }
    else
        for (int i = x_errol - 1; i > x_ide; i--) {
            if (ftabla[y_ide][i].babu != ures)
                return false;
        }
    return true;
}



bool nincsakadalykeresztbe(int x_errol,int x_ide,int y_errol, int y_ide,Babuk ftabla[8][8]) {
    if(y_errol<y_ide) {
        if (x_errol < x_ide){
            for (int j = x_errol + 1, i = y_errol + 1; j < x_ide; ++j, ++i)
                if (ftabla[i][j].babu != ures)
                    return false;
        } else
            for(int j = x_errol -1,i = y_errol + 1; j > x_ide; --j,++i)
                if (ftabla[i][j].babu != ures)
                    return false;
    }
    else
    if (x_errol < x_ide){
        for (int j = x_errol + 1, i = y_errol - 1; j < x_ide; ++j, --i)
            if (ftabla[i][j].babu != ures)
                return false;
    } else
        for(int j = x_errol -1,i = y_errol - 1; j > x_ide; --j,--i)
            if (ftabla[i][j].babu != ures)
                return false;
    return true;
}


Kiraly_pozicio hol_kiraly(Babuk ftabla[8][8]){
    Kiraly_pozicio f;
    for(int i =0; i <8 ; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (ftabla[i][j].babu == kiraly) {
                if (ftabla[i][j].szin == fekete) {
                    f.sk_i = i;
                    f.sk_j = j;
                } else {
                    f.vk_i = i;
                    f.vk_j = j;
                }
            }
        }

    }
    return f;
}

bool van_sakk(Babuk ftabla[8][8], int *kivansakk){
    Kiraly_pozicio a = hol_kiraly(ftabla);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if(ftabla[i][j].babu != ures){
                if(ftabla[i][j].szin == fekete) {
                    if (szabalyoslepes(j, a.vk_j, i, a.vk_i, ftabla)) {
                        *kivansakk = fekete;
                        return true;
                    }

                }else
                    if( szabalyoslepes(j,a.sk_j,i,a.sk_i,ftabla)) {
                        *kivansakk = feher;
                        return true;
                    }

            }
        }
    }
    return false;
}


bool sakkmatt(Babuk ftabla[8][8], int kivansakk){
    Babuk temp;
    for(int i =0; i <8; ++i){
        for(int j =0; j< 8; ++j){
            if(ftabla[i][j].babu != ures && ftabla[i][j].szin != kivansakk)
                for(int k =0; k <8; ++k){
                    for(int l =0; l <8;++l){
                        if(szabalyoslepes(j,l,i,k,ftabla)) {
                            temp.babu = ftabla[k][l].babu;
                            temp.szin = ftabla[k][l].szin;
                            ftabla[k][l] = ftabla[i][j];
                            ftabla[i][j].babu = ures;
                            ftabla[i][j].szin = nincs;
                            if(!van_sakk(ftabla,&kivansakk)) {
                                ftabla[i][j] = ftabla[k][l];
                                ftabla[k][l].babu = temp.babu;
                                ftabla[k][l].szin = temp.szin;
                                return false;
                            }
                            ftabla[i][j] = ftabla[k][l];
                            ftabla[k][l].babu = temp.babu;
                            ftabla[k][l].szin = temp.szin;

                        }
                    }
                }
        }
    }
    return true;
}





