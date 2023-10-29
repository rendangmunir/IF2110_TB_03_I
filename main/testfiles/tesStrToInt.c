#include <stdio.h>
#include "includeADT.h"

int main() {
    STARTWORD();
    int num = WordToInt(currentWord);

    printf("Result: %d\n", num);
}