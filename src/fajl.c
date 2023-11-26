#include "fajl.h"
#include "debugmalloc.h"

int fajlkiiras(FILE *fajl, Babuk ftabla[8][8], bool kijon) { //megnyitja a sakk_jatszma.txt és kiÍrja a jelenlegi sakk állást, ez  menti el az állapotot. Sikertelen müveletnél hiba üzenet.
    fajl = fopen("sakk_jatszma.txt", "w");
    if (fajl == NULL) {
        perror("Nem sikerult a fajlt megnyitni.");
        return 1;
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            fprintf(fajl, "%d:%d ", ftabla[i][j].babu, ftabla[i][j].szin);
        }
    }
    fprintf(fajl, "%d", kijon);
    fclose(fajl);
    return 0;
}

int fajlbeolvasas(FILE *fajl, Babuk ftabla[8][8], bool *kijon) { // megkereso a sakk_jatszma.txt, megnyitja és beolvassa az állást, és, hogy kikövetkezik.Sikertelen müveletnél hiba üzenet.
    fajl = fopen("sakk_jatszma.txt", "r");
    if (fajl == NULL) {
        perror("Nem sikerult a fajlt megnyitni.");
        return 1;
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (fscanf(fajl, "%d:%d", &ftabla[i][j].babu, &ftabla[i][j].szin) != 2) {
                fprintf(stderr, "Hiba volt az olvasás soran.\n");
                fclose(fajl);
                return 1;
            }
        }
    }
    if (fscanf(fajl, "%d", (int *)kijon) != 1) {
        fprintf(stderr, "Hiba volt az olvasás soran.\n");
        fclose(fajl);
        return 1;
    }
    fclose(fajl);
    return 0;
}
