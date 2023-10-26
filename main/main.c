#include <stdio.h>
#include "includeADT.h"
#include "commands.c"

int main() {
    printf("Selamat datang di BurBir. Selamat berkicau!\n\n");

    Word TUTUP_PROGRAM = {"TUTUP_PROGRAM", 13};
    Pengguna PenggunaA = {
            {"Tuan Kil", 8},
            {"pass1", 5}
        };
    Pengguna PenggunaB = {
            {"Tuan Man", 8},
            {"pass2", 5} 
    };
    Pengguna PenggunaC = {
            {"Tuan Bas", 8},
            {"pass2", 5} 
    };
    ELMTPengguna(listUsers, 0) = PenggunaA;
    ELMTPengguna(listUsers, 1) = PenggunaB;
    ELMTPengguna(listUsers, 2) = PenggunaC;
    listUsers.Neff = 3;
    
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