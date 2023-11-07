#include <stdio.h>

#include "sakktabla.h"
#include "lepeskisegitofuggvenyek.h"

int main(void) {
    /*tablakiiras
    printf("Matrix:\n");
    feltolt();
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            printf("%d ", tabla[i][j].babu);
        }
        printf("\n");
    }*/
    /*elsolepesellenorzes
     * feltolt();
    if(szabalyoslepes(tabla[1][1],1))
        printf("lehet");
    else
        printf("nem");

*/
    feltolt();
    if(nincsakadalylinearisan(6,5,7,7))
        printf("nincs\n");
    else
        printf(" akadaly\n");

    if(nincsakadalylinearisan(2,5,0,3))
        printf("nincs");
    else
        printf(" akadaly");

    return 0;
}
