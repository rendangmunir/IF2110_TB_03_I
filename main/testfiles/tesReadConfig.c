#include <stdio.h>
#include "../includeADT.h"

int main() {
    STARTFILE("./config/config-1/pengguna.config");
    while (currentChar != MARK) {
        ADVNEWLINE();
        ADV();
        if (currentChar == ENTER) {
            printf("\n");
        }
        printWord(currentWord);
        printf("(Length: %d)\n", currentWord.Length);
    }

    return 0;
}