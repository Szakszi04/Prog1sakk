#include <stdio.h>
// 1=király, 2=királyno, 3=bastya, 4=futo, 5=huszar, 6=gyalog
int tabla[8][8];
void feltolt(void) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            tabla[i][j] = -1;
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i == 1)
                tabla[i][j] = 6;
            else if (i == 0)
                tabla[i][0] = 3, tabla[i][1] = 5, tabla[i][2] = 4, tabla[i][3] = 2, tabla[i][4] = 1, tabla[i][5] = 4, tabla[i][6] = 5, tabla[i][7] = 3;
        }
    }
    for (int i = 6; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i == 6)
                tabla[i][j] = 6;
            else if (i == 7)
                tabla[i][0] = 3, tabla[i][1] = 5, tabla[i][2] = 4, tabla[i][3] = 2, tabla[i][4] = 1, tabla[i][5] = 4, tabla[i][6] = 5, tabla[i][7] = 3;
        }
    }
}
int main(void) {
    printf("Matrix:\n");
    feltolt();
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            printf("%d ", tabla[i][j]);
        }
        printf("\n");
    }
    return 0;
}
// 1=király, 2=királyno, 3=bastya, 4=futo, 5=huszar, 6=gyalog



//
// Created by adam on 10/31/23.
//
