#include <stdio.h>
#include "includeADT.h"

int main() {
    STARTFILE("../cfg/pengguna.config");
    while (currentChar != MARK) {
        printf("%c", currentChar);
        ADV();
    }

    return 0;
}