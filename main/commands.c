#include <stdio.h>
#include <sys/stat.h>
#include "includeADT.h"

// ================= Initialization =================
// 0a. Misc. Functions
void concatStrings(const char *str1, const char *str2, char *result);
boolean directoryExists(char* filepath);
void ADVUntil(char mark);
DATETIME parseDATETIME();

// 0b. Inisialisasi
void BacaDataConfig(char* prefix, int op, char* suffix);
void BacaProfilPengguna();
void BacaGrafPertemanan();
void BacaKicauan();

// 1. Pengguna
void Daftar();
void Masuk();
void Keluar();
void TutupProgram();
void ListPengguna();
void Muat();

// 2. Profil
void Ganti_Profil();
void Lihat_Profil();
void PrintFoto(Pengguna p);
void Atur_Jenis_Akun();
void Ubah_Foto_Profil();

// 3. Teman

// 4. Permintaan Pertemanan

// 5. Kicauan
void Kicau();
void DisplayKicauan();
void SukaKicauan();
void UbahKicauan();

// 6. Balasan
void Balas();
void DisplayBalasan();
void HapusBalasan();

// 7. Draf Kicauan

// 8. Utas

// X. FYB
void FYB();

// ================= Data =================

// Data
Pengguna currentUser;
boolean isLoggedIn;
boolean runProgram;

// Data Structures
ListStatikPengguna listUsers;
ListDinKicauan listKicauan;
GrafTeman FriendGraph;

// Commands
void Inisialisasi() {
    printf("Silahkan masukan folder konfigurasi untuk dimuat: ");
    
    // Get folder name
    char dir[50];
    scanf("%s", dir);

    // Concat folder name to relative path
    char prefix[] = "./config/";
    char filepath[100];
    concatStrings(prefix, dir, filepath);

    // Check if folder exists
    if (!directoryExists(filepath)) {
        printf("Nama folder yang Anda masukkan tidak ditemukan! Mohon masukkan ulang nama folder.\n");
        Inisialisasi();
    } else {
        BacaDataConfig(filepath, 1, "/pengguna.config");
        BacaDataConfig(filepath, 2, "/kicauan.config");

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

    // 2. Profil
    Word GANTI_PROFIL = {"GANTI_PROFIL", 12};
    Word LIHAT_PROFIL = {"LIHAT_PROFIL", 12};
    Word ATUR_JENIS_AKUN = {"ATUR_JENIS_AKUN", 15};
    Word UBAH_FOTO_PROFIL = {"UBAH_FOTO_PROFIL", 16};

    // 3. Teman

    // 4. Permintaan Pertemanan

    // 5. Kicauan
    Word KICAU = {"KICAU", 5};
    Word KICAUAN = {"KICAUAN", 7};
    Word SUKA_KICAUAN = {"SUKA_KICAUAN", 12};
    Word UBAH_KICAUAN = {"UBAH_KICAUAN", 12};

    // 6. Balasan
    Word BALAS = {"BALAS", 5};
    Word BALASAN = {"BALASAN", 7};
    Word HAPUS_BALASAN = {"HAPUS_BALASAN", 13};

    // 7. Draf Kicauan

    // 8. Utas

    // X. FYB
    Word FYB_STR = {"FYB", 3};

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
    else if (WordEqual(command, GANTI_PROFIL)){
        Ganti_Profil();
    }else if (WordEqual(command, LIHAT_PROFIL)){
        Lihat_Profil();
    }else if (WordEqual(command, ATUR_JENIS_AKUN)){
        Atur_Jenis_Akun();
    }else if (WordEqual(command, UBAH_FOTO_PROFIL)){
        Ubah_Foto_Profil();
    }

    // 3. Teman

    // 4. Permintaan Pertemanan

    // 5. Kicauan
    else if (WordEqual(command, KICAU)) {
        Kicau();
    } else if (WordEqual(command, KICAUAN)) {
        DisplayKicauan();
    }

    // 6. Balasan
    else if (WordEqual(command, BALAS)) {
        // Balas();
    } else if (WordEqual(command, BALASAN)) {
        // DisplayBalasan();
    } else if (WordEqual(command, HAPUS_BALASAN)) {
        // HapusBalasan();
    }
    // 7. Draf Kicauan

    // 8. Utas

    // X. FYB
    else if (WordEqual(command, FYB_STR)) {
        FYB();
    }
    
    else {
        printf("Perintah yang dimasukkan tidak dikenali! Mohon memasukkan ulang perintah anda.\n");
    }
}

// ================= Functions =================

// 0a. Additional Functions
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

void ADVUntil(char mark) {
    int i = 0;
    while (currentChar != mark) {
        currentWord.TabWord[i] = currentChar;
        ADV();
        i += 1;
    }
    ADV();
    currentWord.Length = (i < NMax) ? i : NMax;
}

DATETIME parseDATETIME() {
    DATETIME t;

    // Day
    ADVUntil('/');
    int day = WordToInt(currentWord);

    // Month
    ADVUntil('/');
    int month = WordToInt(currentWord);

    // Year
    ADVUntil(BLANK);
    int year = WordToInt(currentWord);

    // Hour
    ADVUntil(':');
    int hour = WordToInt(currentWord);

    // Minutes
    ADVUntil(':');
    int min = WordToInt(currentWord);

    // Seconds
    int i = 0;
    while (i < 2) {
        currentWord.TabWord[i] = currentChar;
        ADV();
        i += 1;
    }
    currentWord.Length = (i < NMax) ? i : NMax;
    int sec = WordToInt(currentWord);
    ADV();

    CreateDATETIME(&t, day, month, year, hour, min, sec);
    return t;
}

// 0b. Inisialisasi
void BacaDataConfig(char* prefix, int op, char* suffix) {
    char filepath[120];

    concatStrings(prefix, suffix, filepath);
    // printf("%s\n", filepath);

    // Parse file
    STARTFILE(filepath);
    ADVNEWLINE();

    int itemCount = WordToInt(currentWord);
    // printf("Usercount: %d\n", itemCount);
    for (int i = 0; i < itemCount; i++) {
        switch (op) {
        case 1:
            BacaProfilPengguna();
            break;
        case 2:
            BacaKicauan();
            break;
        // case 3:
        //     char suffix[] = "/balasan.config";
        //     break;
        // case 4:
        //     char suffix[] = "/draf.config";
        //     break;
        // default:
        //     char suffix[] = "/utas.config";
        //     break;
        }        
    }

    if (op == 1) {
        BacaGrafPertemanan();
    }
}

void BacaProfilPengguna() {
    Pengguna p;
    Word empty = {";", 1};
    // 1 Nama
    ADVNEWLINE();
    Word nama = currentWord;

    // 2 Password
    ADVNEWLINE();
    Word pass = currentWord;

    // 3 Bio
    ADVNEWLINE();
    Word bio = (!currentWord.Length) ? empty : currentWord;

    // 4 NoHP
    ADVNEWLINE();
    // int noHP = (!currentWord.Length) ? 0 : WordToInt(currentWord);
    Word noHP = (!currentWord.Length) ? empty : currentWord;

    // 5 Weton
    ADVNEWLINE();
    Word weton = (!currentWord.Length) ? empty : currentWord;

    // 6 Jenis Akun
    ADVNEWLINE();
    Word jenis = (!currentWord.Length) ? empty : currentWord;

    // 7-11 Foto Profil
    MatrixChar profilepic;
    readMatrixChar(&profilepic, 5, 10);

    // printWord(nama); printf("\n");
    // printWord(pass); printf("\n");
    // printWord(bio); printf("\n");
    // printWord(noHP); printf("\n");
    // printWord(weton); printf("\n");
    // printWord(jenis); printf("\n");
    // displayMatrixChar(profilepic);
    Pengguna user = {nama, pass, bio, noHP, weton, jenis, profilepic};
    // PrintFoto(user);
    insertLastPengguna(&listUsers, user);
}

void BacaGrafPertemanan() {
    int n = listLengthPengguna(listUsers);
    readMatrixChar(&FriendGraph, n, n);

    displayMatrixChar(FriendGraph);
}

void BacaKicauan() {
    // ID
    ADVNEWLINE();
    Word idWord = currentWord;
    int id = WordToInt(idWord);

    // Text
    ADVNEWLINE();
    Word text = currentWord;

    // Likes
    ADVNEWLINE();
    Word likesWord = currentWord;
    int likes = WordToInt(likesWord);

    // Author
    ADVNEWLINE();
    Word author = currentWord;

    // Datetime
    DATETIME t = parseDATETIME();

    // printf("%d\n", id);
    // printWord(text); printf("\n");
    // printf("%d\n", likes);
    // printWord(author); printf("\n");
    // TulisDATETIME(t); printf("\n");

    Kicauan k = {id, text, likes, author, t};

    insertLastKicauan(&listKicauan, k);
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

void Ganti_Profil(){
    if (!isLoggedIn){
        printf("Anda belum login! Masuk terlebih dahulu untuk mengganti profil\n");
    }else{
        printf("| Nama: "); printWord(currentUser.Nama); printf("\n");
        printf("| Bio Akun: "); printWord(currentUser.Bio); printf("\n");
        printf("| No HP: %d\n", currentUser.noHP);
        printf("| Weton: "); printWord(currentUser.Weton); printf("\n\n");
        Word weton[] = {{"Pahing", 6}, {"Kliwon", 6}, {"Wage", 6}, {"Pon",3}, {"Legi", 4}};

        printf("Masukkan Bio Akun:\n");
        STARTSENTENCE();

        Word bio = currentWord;
        currentUser.Bio=bio;
        printf("\n");

        boolean validnr=false;
        while (!validnr)
        {
            printf("Masukkan No HP:\n");
            STARTSENTENCE();
            for (int i=0; i<currentWord.Length; i++){
                if (currentWord.TabWord[i]>'0' && currentWord.TabWord[i]<'9'){
                    validnr=true;
                }
            }
            if (!validnr){
                printf("\n");
                printf("No HP tidak valid, Masukkan lagi yuk!\n");
                printf("\n");
            }
        }
        currentUser.noHP= (currentWord);
        printf("\n");

        boolean validwt=false;
        while (!validwt)
        {
            printf("Masukkan Weton:\n");
            STARTSENTENCE();

            for (int i=0; i<4;i++){
                if (WordEqual(currentWord,weton[i])){
                    validwt=true;
                }
            }
            if (!validwt){
                printf("\n");
                printf("Weton anda tidak valid\n");
                printf("\n");
            }
        }
        currentUser.Weton=currentWord;
        printf("Profil anda sudah berhasil diperbarui!\n\n");
    }
}

void PrintFoto(Pengguna p){
    MatrixChar M = p.FotoProfil;
    for (int i=0; i<M.rowEff; i++){
        for (int j=0; j<M.colEff; j=j+2){
            if(M.mem[i][j]=='R'){
                print_red(M.mem[i][j+1]);
            }else if (M.mem[i][j]=='G'){
                print_green(M.mem[i][j+1]);
            }else{
                print_blue(M.mem[i][j+1]);
            }
        }
        printf("\n");
    }
}

void PrintProfil(Pengguna p){
    printf("| Nama: "); printWord(p.Nama); printf("\n");
    printf("| Bio Akun: "); printWord(p.Bio); printf("\n");
    printf("| No HP: "); printWord(p.noHP); printf("\n");
    printf("| Weton: "); printWord(p.Weton); printf("\n\n");
    printf("Foto profil akun "); printWord(p.Nama); printf("\n");
    PrintFoto(p); printf("\n");
}

void Lihat_Profil(){

    if (!isLoggedIn){
        printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
    }else{
        STARTSENTENCE();

        Word name = currentWord;
        int userIndex = indexOfUser(listUsers, name);

        if (WordEqual(currentWord, currentUser.Nama)){
            PrintProfil(currentUser);
        }else{
            if (userIndex == IDX_UNDEF){
                printf("Akun ini tidak terdaftar di BurBir!\n");
            }else{
                Pengguna user = ELMTPengguna(listUsers, userIndex);
                Word Publik = {"Publik", 6};
                if(WordEqual(user.JenisAkun, Publik)){
                    PrintProfil(user);
                }else{
                    //cek apakah currentuser mengikuti user (Isfollowing(currentUser, user))
                    PrintProfil(user); 
                }
            }
        }
    }
}

void Atur_Jenis_Akun(){
    if (!isLoggedIn){
        printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
    }else{
        Word type = currentUser.JenisAkun;
        Word Publik = {"Publik", 6};
        Word Privat = {"Privat", 6};
        Word YA = {"YA", 2};
        printf("Saat ini, akun Anda adalah akun "); printWord(type); printf(".\n");
        if (WordEqual(type, Publik)){
            printf("Ingin mengubah ke akun Privat?\n");
            printf("(YA/TIDAK) ");
            STARTSENTENCE();
            if (WordEqual(currentWord, YA))
            {
                currentUser.JenisAkun=Privat;
                printf("Akun anda sudah diubah menjadi akun Privat");
            }else{
                printf("Pengubahan jenis akun dibatalkan\n");
            }
        }else{
            printf("Ingin mengubah ke akun Publik?\n");
            printf("(YA/TIDAK) ");
            STARTSENTENCE();
            if (WordEqual(currentWord, YA))
            {
                currentUser.JenisAkun=Publik;
                printf("Akun anda sudah diubah menjadi akun Publik\n");
            }else{
                printf("Pengubahan jenis akun dibatalkan\n");
            }
        }
    }    
}

void Ubah_Foto_Profil(){
    if (!isLoggedIn){
        printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
    }else{
        printf("Foto profil Anda saat ini adalah\n");
        PrintFoto(currentUser); printf("\n\n");
        printf("Masukkan foto profil yang baru\n");
        MatrixChar fotoprofil;
        createMatrixChar(5, 10, &fotoprofil);
        START(); IgnoreBlanks(); IgnoreEnters();
        int i, j;
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 10; j++) {
                ELMT_MATRIXCHAR(fotoprofil, i ,j) = currentChar;
                ADV();
                IgnoreBlanks(); IgnoreEnters();
            }
            IgnoreEnters();
        }
        currentUser.FotoProfil=fotoprofil;
        printf("\n");
        printf("Foto profil anda sudah berhasil diganti!\n\n");
        PrintFoto(currentUser);
    }
}

// 3. Teman

// 4. Permintaan Pertemanan

// 5. Kicauan
void PrintKicauan(Kicauan k) {
    int id = k.id;
    Word text = k.text;
    int likes = k.likes;
    Word author = k.author;
    DATETIME datetime = k.datetime;
    
    printf("\n");
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

void DisplayKicauan() {
    int kicauanCount = listLengthKicauan(listKicauan);
    for (int i = (kicauanCount - 1); i >= 0; i--) {
        Kicauan k = ELMT_Kicauan(listKicauan, i);
        if (WordEqual(k.author, currentUser.Nama)) {
            PrintKicauan(k);
        }
    }
}

// 6. Balasan
void Balas() {
    
}

// 7. Draf Kicauan

// 8. Utas

// X. FYB
void FYB() {
    MaxHeapKicauan h = createMaxHeapKicauan(listKicauan);
    HeapifyListKicauan(&h);

    while (MaxHeapLengthKicauan(h) > 1) {
        ElTypeKicauan root;
        PopMaxHeap(&h, &root);

        PrintKicauan(root);
    }
}