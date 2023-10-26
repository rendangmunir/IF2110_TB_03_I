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
    
    isLoggedIn = false;
    boolean runProgram = true;
    while (runProgram) {
        printf(">> ");
        STARTSENTENCE();

        Word command = currentWord;
        // printf("%d\n", indexOfUser(listUsers, command));

        if (WordEqual(command, TUTUP_PROGRAM)) {
            printf("Terimakasih sudah menggunakan BurBir! Semoga kita dipertemukan lagi!\n");
            runProgram = false; 
        } else {
            RunCommand(command);
        }
    }

    return 0;
}