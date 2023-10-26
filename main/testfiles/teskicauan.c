#include <stdio.h>
#include "includeADT.h"

int main() {
    ListDinKicauan t;
    CreateListDinKicauan(&t, 5);

    for (int i = 0; i < 10; i++) {
        Kicauan k = {i + 1};
        insertLastKicauan(&t, k);
    }

    return 0;
}