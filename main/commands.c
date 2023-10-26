#include <stdio.h>
#include "includeADT.h"
#include "functions.c"

void Daftar();
void Masuk();
void Keluar();
void ListPengguna();

// Data
Pengguna currentUser;
boolean isLoggedIn;
ListStatikPengguna listUsers;

// Commands
void RunCommand(Word command) {
    // Variables
    Word DAFTAR = {"DAFTAR", 6};
    Word MASUK = {"MASUK", 5};
    Word KELUAR = {"KELUAR", 6};
    Word TUTUP_PROGRAM = {"TUTUP_PROGRAM", 13};
    Word LISTPENGGUNA = {"LISTPENGGUNA", 12};

    // Run commands
    if (WordEqual(command, DAFTAR)) {
        Daftar();
    } else if (WordEqual(command, MASUK)) {
        Masuk();
    } else if (WordEqual(command, KELUAR)) {
        // Keluar();
    } else if (WordEqual(command, LISTPENGGUNA)) {
        ListPengguna();
    }
    
    else {
        printf("Perintah yang dimasukkan tidak dikenali! Mohon memasukkan ulang perintah anda.\n");
    }
}

void Daftar() {
    if (isLoggedIn) {
        printf("\nAnda sudah masuk. Keluar terlebih dahulu untuk melakukan daftar.\n");
    } else {
        printf("\n\nMasukkan nama:\n");
        STARTSENTENCE();

        Word name = currentWord;
        int userIndex = indexOfUser(listUsers, name);

        Word pass;
        if (userIndex != IDX_UNDEF_PENGGUNA) {
            printf("Wah, sayang sekali nama tersebut sudah diambil!");
            Daftar();
        } else {
            do {
                printf("\nMasukkan kata sandi:\n");
                STARTSENTENCE();

                pass = currentWord;
                if (pass.Length > 20) {
                    printf("Kata sandi tidak boleh lebih dari 20 karakter!");
                }
            } while (pass.Length > 20);
            
            Pengguna newUser = {name, pass};
            insertLastPengguna(&listUsers, newUser);

            printf("Pengguna telah berhasil terdaftar! Silahkan ketik MASUK; untuk menikmati fitur-fitur BurBir.\n");
        }

    }
}

void Masuk() {
    if (isLoggedIn) {
        printf("\nWah Anda sudah masuk. Keluar dulu yuk!.\n");
    } else {
        printf("\n\nMasukkan nama:\n");
        STARTSENTENCE();

        Word name = currentWord;
        int userIndex = indexOfUser(listUsers, name);
        
        Word pass, userPassword;
        boolean correctPassword;
        if (userIndex == IDX_UNDEF_PENGGUNA) {
            printf("Wah, nama yang Anda cari tidak ada. Masukkan nama lain!");
            Masuk();
        } else {
            Pengguna user = ELMTPengguna(listUsers, userIndex);
            userPassword = user.Password;

            do {
                printf("\nMasukkan kata sandi:\n");
                STARTSENTENCE();

                pass = currentWord;
                if (WordEqual(pass, userPassword)) {
                    correctPassword = true;
                } else {
                    correctPassword = false;
                    printf("Wah, kata sandi yang Anda masukkan belum tepat. Periksa kembali kata sandi Anda!");
                }
            } while (!correctPassword);

            printf("Anda telah berhasil masuk dengan nama pengguna ");
            printWord(user.Nama);
            printf(". Mari menjelajahi BurBir bersama Ande-Ande Lumut!\n");
        }
    }
}

void ListPengguna() {
    int i;
    for (i = 0; i < listLengthPengguna(listUsers); i++) {
        Pengguna user = ELMTPengguna(listUsers, i);
        printWord(user.Nama);
    }
}