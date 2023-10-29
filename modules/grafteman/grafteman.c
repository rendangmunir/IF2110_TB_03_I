#include <stdio.h>

#include "grafteman.h"

/**** Konstruktor ****/
GrafTeman createGrafTeman(int users) {
    GrafTeman g;
    createMatrixChar(users, users, &g);

    return g;
}