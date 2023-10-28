#include <stdio.h>
#include "includeADT.h"
#include "commands.c"

int main() {
    printf("Selamat datang di BurBir.\n");
    printf("Aplikasi untuk studi kualitatif mengenai perilaku manusia dengan menggunakan metode (pengambilan data berupa) Focused Group Discussion kedua di zamannya.\n");

    Inisialisasi();
    
    // Initialization
    isLoggedIn = false;
    runProgram = true;

    // Main Program
    while (runProgram) {
        printHeaders();
        STARTWORD();

        Word command = currentWord;
        RunCommand(command);
    }

    return 0;
}