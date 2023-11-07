#ifndef NAGGYHAZIAMIGNEMLESZMEGJAVULVA_ENUM_H
#define NAGGYHAZIAMIGNEMLESZMEGJAVULVA_ENUM_H

typedef enum babukkoddal{
    ures = 0,
    kiraly = 1,
    kiralyno = 2,
    bastya = 3,
    futo = 4,
    huszar = 5,
    gyalog = 6,
} babukkoddal;

typedef enum szinek{
    feher = -1,
    fekete = 1
}szinek;

typedef struct babuk{
    babukkoddal babu ;
    szinek szin;
}babuk;




#endif //NAGGYHAZIAMIGNEMLESZMEGJAVULVA_ENUM_H
