#include <stdio.h>
#include "includeADT.h"
#include "functions.c"

int main() {
    printf("Selamat datang di Burbir. Selamat berkicau!\n\n");

    boolean runProgram = true;

    while (runProgram) {
        printf(">> ");
        STARTWORD();

        Word command = currentWord;
        Word keluar = {"KELUAR", 6};

        printWord(command);

        if (WordEqual(command, keluar)) {
            runProgram = false; 
        }
    }
    return 0;
}