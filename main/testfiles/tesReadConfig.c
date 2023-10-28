#include <stdio.h>
#include "../includeADT.h"

int main() {
    STARTFILE("./config/config-1/pengguna.config");
    while (currentChar != MARK) {
        ADVNEWLINE();

        printWord(currentWord);
        // printf("(Length: %d)\n", currentWord.Length);
        printf("\n");
    }

    return 0;
}