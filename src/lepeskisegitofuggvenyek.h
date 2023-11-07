
#ifndef NAGGYHAZIAMIGNEMLESZMEGJAVULVA_LEPESKISEGITOFUGGVENYEK_H
#define NAGGYHAZIAMIGNEMLESZMEGJAVULVA_LEPESKISEGITOFUGGVENYEK_H
#include <stdbool.h>
#include "sakktabla.h"

bool nincsakadalylinearisan(int x_errol,int x_ide,int y_errol, int y_ide) {
    if (x_errol < x_ide) // felfele viszgaljuk
        for (int i = x_errol + 1; i < x_ide; i++) {
            if (tabla[i][y_ide].babu != ures)
                return false;
        }
    else if (x_errol > x_ide)
        for (int i = x_errol - 1; i > x_ide; i--) {
            if (tabla[i][y_ide].babu != ures)
                return false;
        }
    else if (y_errol < y_ide)
        for (int i = y_errol + 1; i < y_ide; i++) {
            if (tabla[x_ide][i].babu != ures)
                return false;
        }
    else
        for (int i = y_errol - 1; i > y_ide; i--) {
            if (tabla[x_ide][i].babu != ures)
                return false;
        }
    return true;
}

bool nincsakadalykeresztbe(int x_errol,int x_ide,int y_errol, int y_ide) {
    if(x_errol<x_ide) {
        if (y_errol < y_ide){
            for (int j = y_errol + 1, i = x_errol + 1; j < y_ide; ++j, ++i)
                if (tabla[i][j].babu != ures)
                    return false;
        } else
            for(int j = y_errol -1,i = x_errol + 1; j > y_ide; --j,++i)
                if (tabla[i][j].babu != ures)
                    return false;
    }
    else
        if (y_errol < y_ide){
            for (int j = y_errol + 1, i = x_errol - 1; j < y_ide; ++j, --i)
                if (tabla[i][j].babu != ures)
                    return false;
    } else
            for(int j = y_errol -1,i = x_errol - 1; j > y_ide; --j,--i)
                if (tabla[i][j].babu != ures)
                    return false;
    return true;
}



#endif //NAGGYHAZIAMIGNEMLESZMEGJAVULVA_LEPESKISEGITOFUGGVENYEK_H
