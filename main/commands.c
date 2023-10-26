#include <stdio.h>
#include "includeADT.h"

void Daftar();
void Masuk();
void Keluar();
void TutupProgram();
void ListPengguna();

// Data
Pengguna currentUser;
boolean isLoggedIn;
boolean runProgram;

// Data Structures
ListStatikPengguna listUsers;

// Commands
void RunCommand(Word command) {
    // ================= Variables =================
    // 1. Pengguna
    Word DAFTAR = {"DAFTAR", 6};
    Word MASUK = {"MASUK", 5};
    Word KELUAR = {"KELUAR", 6};
    Word TUTUP_PROGRAM = {"TUTUP_PROGRAM", 13};
    Word LISTPENGGUNA = {"LISTPENGGUNA", 12};

    // 5. Kicauan
    Word KICAU = {"KICAU", 5};
    Word KICAUAN = {"KICAUAN", 7};
    Word SUKA_KICAUAN = {"SUKA_KICAUAN", 12};
    Word UBAH_KICAUAN = {"UBAH_KICAUAN", 12};

    // ================= Commands =================
    // 1. Pengguna
    if (WordEqual(command, DAFTAR)) {
        Daftar();
    } else if (WordEqual(command, MASUK)) {
        Masuk();
    } else if (WordEqual(command, KELUAR)) {
        // Keluar();
    } else if (WordEqual(command, LISTPENGGUNA)) {
        ListPengguna();
    } else if (WordEqual(command, TUTUP_PROGRAM)) {
        TutupProgram();
    }

    // 2. Profil

    // 3. Teman

    // 4. Permintaan Pertemanan

    // 5. Kicauan

    // 6. Balasan

    // 7. Draf Kicauan

    // 8. Utas
    
    else {
        printf("Perintah yang dimasukkan tidak dikenali! Mohon memasukkan ulang perintah anda.\n");
    }
}

// ================= Functions =================

// 0. Additional Functions
void printHeaders() {
    printf("\n==================================================\n");
    if (isLoggedIn) {
        printf("Nama User: ");
        printWordNewline(currentUser.Nama);
        printf("\n");
    }
    printf(">> ");
}

// 1. Pengguna
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

            isLoggedIn = true;
            currentUser = ELMTPengguna(listUsers, userIndex);
        }
    }
}

void TutupProgram() {
    printf("Terimakasih sudah menggunakan BurBir! Semoga kita dipertemukan lagi!\n");
    runProgram = false; 
}

void ListPengguna() {

    printf("\nDaftar pengguna: \n");
    int i;
    for (i = 0; i < listLengthPengguna(listUsers); i++) {
        Pengguna user = ELMTPengguna(listUsers, i);
        printWord(user.Nama);
        printf("\n");
    }
}