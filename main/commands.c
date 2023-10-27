#include <stdio.h>
#include <sys/stat.h>
#include "includeADT.h"

// ================= Initialization =================
// 0. Misc. Functions
void concatStrings(const char *str1, const char *str2, char *result);
boolean directoryExists(char* filepath);

// 1. Pengguna
void Daftar();
void Masuk();
void Keluar();
void TutupProgram();
void ListPengguna();
void Muat();

// 2. Profil

// 3. Teman

// 4. Permintaan Pertemanan

// 5. Kicauan
void Kicau();
void DisplayKicauan();
void SukaKicauan();
void UbahKicauan();

// 6. Balasan

// 7. Draf Kicauan

// 8. Utas

// ================= Data =================

// Data
Pengguna currentUser;
boolean isLoggedIn;
boolean runProgram;

// Data Structures
ListStatikPengguna listUsers;
ListDinKicauan listKicauan;

// Commands
void Inisialisasi() {
    printf("Silahkan masukan folder konfigurasi untuk dimuat: ");
    
    // Get folder name
    char dir[50];
    scanf("%s", &dir);

    // Concat folder name to relative path
    char prefix[] = "./config/";
    char filepath[100];
    concatStrings(prefix, dir, filepath);

    // Check if folder exists
    if (!directoryExists(filepath)) {
        printf("Nama folder yang Anda masukkan tidak ditemukan! Mohon masukkan ulang nama folder.\n");
        Inisialisasi();
    } else {
        printf("File konfigurasi berhasil dimuat! Selamat berkicau!\n");
    }
}

void RunCommand(Word command) {
    // ================= Variables =================
    // 1. Pengguna
    Word DAFTAR = {"DAFTAR", 6};
    Word MASUK = {"MASUK", 5};
    Word KELUAR = {"KELUAR", 6};
    Word TUTUP_PROGRAM = {"TUTUP_PROGRAM", 13};
    Word LISTPENGGUNA = {"LISTPENGGUNA", 12};
    Word MUAT = {"MUAT", 4};

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
        Keluar();
    } else if (WordEqual(command, LISTPENGGUNA)) {
        ListPengguna();
    } else if (WordEqual(command, TUTUP_PROGRAM)) {
        TutupProgram();
    } else if (WordEqual(command, MUAT)) {
        // Muat();
    } else if (!isLoggedIn) {
        printf("Perintah yang dimasukkan tidak dikenali atau Anda belum login! Silahkan jalankan perintah MASUK, DAFTAR, MUAT, atau TUTUP_PROGRAM.\n");
    }

    // 2. Profil

    // 3. Teman

    // 4. Permintaan Pertemanan

    // 5. Kicauan
    else if (WordEqual(command, KICAU)) {
        Kicau();
    }

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

void printTab(int count) {
    int i;
    for (i = 1; i < count; i++) {
        printf("    ");
    }
    printf(" |   ");
}

void concatStrings(const char *str1, const char *str2, char *result) {
    int i = 0;
    while (str1[i] != '\0') {
        result[i] = str1[i];
        i++;
    }
    
    int j = 0;
    while (str2[j] != '\0') {
        result[i] = str2[j];
        i++;
        j++;
    }
    
    result[i] = '\0';
}

boolean directoryExists(char* filepath) {
    struct stat info;
    if (stat(filepath, &info) != 0) {
        return false;
    }
    return S_ISDIR(info.st_mode);
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

void Keluar() {
    if (!isLoggedIn) {
        printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
    } else {
        isLoggedIn = false;
        printf("Anda berhasil logout. Sampai jumpa di pertemuan berikutnya!\n");
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

// 2. Profil

// 3. Teman

// 4. Permintaan Pertemanan

// 5. Kicauan
void PrintKicauan(Kicauan k) {
    int id = k.id;
    Word text = k.text;
    int likes = k.likes;
    Word author = k.author;
    DATETIME datetime = k.datetime;
    
    printTab(1);
    printf("ID = %d\n", id);
    
    printTab(1);
    printWordNewline(author);

    printTab(1);
    TulisDATETIME(datetime);
    printf("\n");

    printTab(1);
    printWordNewline(text);
    
    printTab(1);
    printf("Disukai: %d\n", likes);
}

void Kicau() {
    printf("Masukkan kicauan: \n");

    STARTSENTENCE();
    int len = currentWord.Length;
    len = (len < 280) ? len : 280;
    currentWord.Length = len;
    printf("\n");
    
    int i;
    int count = 0;
    char currchar;
    for (i = 0; i < len; i++) {
        currchar = currentWord.TabWord[i];
        count += (currchar != BLANK) ? 1 : 0; 
    }

    if (!count) {
        printf("Kicauan tidak boleh hanya berisi spasi!\n");
        Kicau();
    } else {
        int id = listLengthKicauan(listKicauan) + 1;
        Word text = currentWord;
        int likes = 0;
        Word author = currentUser.Nama;
        DATETIME datetime = GetDateTime();

        Kicauan submittedKicauan = {id, text, likes, author, datetime};

        printf("Selamat! kicauan telah diterbitkan!\nDetil kicauan:\n");
        PrintKicauan(submittedKicauan);

        insertLastKicauan(&listKicauan, submittedKicauan);
    }
}

// 6. Balasan

// 7. Draf Kicauan

// 8. Utas