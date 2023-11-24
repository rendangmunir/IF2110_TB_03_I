#include <stdio.h>
#include <sys/stat.h>
#include "includeADT.h"

// ================= Initialization =================
// 0a. Misc. Functions
void concatStrings(const char *str1, const char *str2, char *result);
boolean directoryExists(char* filepath);
void ADVUntil(char mark);
DATETIME parseDATETIME();
void printTab(int count);

// 0b. Inisialisasi
void BacaDataConfig(char* prefix, int op, char* suffix);
void BacaProfilPengguna();
void BacaGrafPertemanan();
void BacaKicauan();
void BacaBalasan();
void BacaDraf();
void BacaUtas(int IDUtas);

void simpanDATETIME(FILE* file, DATETIME t);
void SimpanDataConfig(char* foldername, int op, char* suffix);
void SimpanKicauan(char* filepath);
void SimpanBalasan(char* filepath);
void SimpanDraf(char* filepath);
void SimpanUtas(char* filepath);

// 1. Pengguna
int indexOfPengguna(Word nama);
void Daftar();
void Masuk();
void Keluar();
void TutupProgram();
void ListPengguna();
void Muat();
void Simpan();

// 2. Profil
void Ganti_Profil();
void Lihat_Profil();
void PrintFoto(Pengguna p);
void Atur_Jenis_Akun();
void Ubah_Foto_Profil();

// 3. Teman
boolean IsTeman(Word user1, Word user2);
void Daftar_Teman(Pengguna p);
void Hapus_Teman(Pengguna p);

// 4. Permintaan Pertemanan
void Make_Pqueue(PrioQueueChar p);
void Tambah_Teman(Pengguna p);
void Daftar_Permintaan_Perteman(Pengguna p);
void Setujui_Pertemanan(Pengguna p);

// 5. Kicauan
int indexOfKicauan(int id);
void Kicau();
void DisplayKicauan();
void SukaKicauan();
void UbahKicauan();

// 6. Balasan
int hitungKicauanDenganBalasan();
void SimpanTreeBalasan(FILE* file, TreeBalasan t);
void Balas();
void DisplayBalasan();
void HapusBalasan();

// 7. Draf Kicauan
int JumlahPenggunaDenganDraf();
void BuatDraf();
void ProsesDraf(Kicauan Draf);
void PrintDraf(Kicauan Draf);
void LihatDraf();

// 8. Utas
void CetakUtas();
void SambungUtas();
void HapusUtas();
void CetakUtas();
void Utas();

// 9. Tagar

// 10. Kelompok Teman
void KelompokTeman();

// 11. FYB
void FYB();

// ================= Data =================

// Data
Pengguna currentUser;
boolean isLoggedIn;
boolean runProgram;
int JumlahUtas = 0;
// Data Structures
ListStatikPengguna listUsers;
ListDinKicauan listKicauan;
GrafTeman FriendGraph;

// ================= Commands =================
void Inisialisasi() {
    printf("Silahkan masukan folder konfigurasi untuk dimuat: ");
    
    // Get folder name
    char dir[50];
    scanf("%s", dir);

    // Concat folder name to relative path
    char prefix[] = "./config/";
    char filepath[100];
    concatStrings(prefix, dir, filepath);
    // printf("Filepath: %s\n", filepath);
    // Check if folder exists
    if (!directoryExists(filepath)) {
        printf("Nama folder yang Anda masukkan tidak ditemukan! Mohon masukkan ulang nama folder.\n");
        Inisialisasi();
    } else {
        // printf("Masuk pembacaan\n");
        BacaDataConfig(filepath, 1, "/pengguna.config");
        // printf("Success Pengguna\n");
        BacaDataConfig(filepath, 2, "/kicauan.config");
        // printf("Success Kicauan\n");
        BacaDataConfig(filepath, 3, "/balasan.config");
        // printf("Success Balasan\n");
        BacaDataConfig(filepath, 4, "/draf.config");
        BacaDataConfig(filepath, 5, "/utas.config");

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
    Word SIMPAN = {"SIMPAN", 6};

    // 2. Profil
    Word GANTI_PROFIL = {"GANTI_PROFIL", 12};
    Word LIHAT_PROFIL = {"LIHAT_PROFIL", 12};
    Word ATUR_JENIS_AKUN = {"ATUR_JENIS_AKUN", 15};
    Word UBAH_FOTO_PROFIL = {"UBAH_FOTO_PROFIL", 16};

    // 3. Teman
    Word DAFTAR_TEMAN = {"DAFTAR_TEMAN", 12};
    Word HAPUS_TEMAN = {"HAPUS_TEMAN", 11};

    // 4. Permintaan Pertemanan
    Word TAMBAH_TEMAN = {"TAMBAH_TEMAN", 12};
    Word DAFTAR_PERMINTAAN_PERTEMANAN = {"DAFTAR_PERMINTAAN_PERTEMANAN", 28};
    Word SETUJUI_PERTEMANAN = {"SETUJUI_PERTEMANAN", 18};

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
    Word BUAT_DRAF = {"BUAT_DRAF", 9};
    Word LIHAT_DRAF = {"LIHAT_DRAF", 10};
    
    // 8. Utas
    Word UTAS = {"UTAS", 4};
    Word SAMBUNG_UTAS = {"SAMBUNG_UTAS", 12};
    Word HAPUS_UTAS = {"HAPUS_UTAS", 10};
    Word CETAK_UTAS = {"CETAK_UTAS", 10};

    // X. Kelompok Teman
    Word KELOMPOK_TEMAN = {"KELOMPOK_TEMAN", 14};

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
    } else if (WordEqual(command, MUAT) && !isLoggedIn) {
        // Muat();
    } else if (!isLoggedIn) {
        printf("Perintah yang dimasukkan tidak dikenali atau Anda belum login! Silahkan jalankan perintah MASUK, DAFTAR, MUAT, atau TUTUP_PROGRAM.\n");
    } else if (WordEqual(command, SIMPAN)) {
        Simpan();
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
    else if (WordEqual(command, DAFTAR_TEMAN)) {
        Daftar_Teman(currentUser);
    } else if (WordEqual(command, HAPUS_TEMAN)) {
        Hapus_Teman(currentUser);
    }

    // 4. Permintaan Pertemanan
        // 4. Permintaan Pertemanan
    else if (WordEqual(command, TAMBAH_TEMAN)){
        Tambah_Teman(currentUser);
    } else if (WordEqual(command, DAFTAR_PERMINTAAN_PERTEMANAN)){
        Daftar_Permintaan_Perteman(currentUser);
    } else if (WordEqual(command, SETUJUI_PERTEMANAN)){
        Setujui_Pertemanan(currentUser);
    }

    // 5. Kicauan
    else if (WordEqual(command, KICAU)) {
        Kicau();
    } else if (WordEqual(command, KICAUAN)) {
        DisplayKicauan();
    }

    // 6. Balasan
    else if (WordEqual(command, BALAS)) {
        Balas();
    } else if (WordEqual(command, BALASAN)) {
        DisplayBalasan();
    } else if (WordEqual(command, HAPUS_BALASAN)) {
        HapusBalasan();
    }
    // 7. Draf Kicauan
    else if(WordEqual(command, BUAT_DRAF)){
        BuatDraf();
    } else if (WordEqual(command, LIHAT_DRAF)){
        LihatDraf();
    }
    // 8. Utas
    else if (WordEqual(command, UTAS)) {
        Utas(&listKicauan);
    } else if (WordEqual(command, SAMBUNG_UTAS)) {
        SambungUtas();
    } else if (WordEqual(command, HAPUS_UTAS)) {
        HapusUtas();
    } else if (WordEqual(command, CETAK_UTAS)) {
        CetakUtas();
    }

    // X. Kelompok Teman
    else if (WordEqual(command, KELOMPOK_TEMAN)) {
        KelompokTeman();
    }

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
        printWordNewline(currentUser.Nama); printf("\n");
        printf("Jumlah pengguna dengan draf: %d\n", JumlahPenggunaDenganDraf());
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
    int itemCount;

    concatStrings(prefix, suffix, filepath);
    // printf("%s\n", filepath);

    // Parse file
    STARTFILE(filepath);
    if (currentChar != '0') {
        ADVNEWLINE();
        itemCount = WordToInt(currentWord);
    } else {
        itemCount = 0;
    }
    // printf("Success Baca Config\n");
    int IDUtas = 1;
    for (int i = 0; i < itemCount; i++) {
        switch (op) {
        case 1:
            // printf("Success Switch \n");
            BacaProfilPengguna();
            break;
        case 2:
            BacaKicauan();
            break;
        case 3:
            BacaBalasan();
            break;
        case 4:
            BacaDraf();
            break;
        case 5:
            BacaUtas(IDUtas);
            IDUtas += 1;
            JumlahUtas += 1;
            break;
        }        
    }

    if (op == 1 && itemCount > 0) {
        BacaGrafPertemanan();
    }
}

void BacaProfilPengguna() {
    // printf("Masuk Baca Profil\n");
    Pengguna p;
    Word empty = {";", 1};
    // printf("Success 1\n");
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

    // Friend Request
    PrioQueueChar friendreq;
    MakeEmpty_PQueue(&friendreq, 20);

    // Miscellaneous
    int id = listLengthPengguna(listUsers) + 1;
    Stack stackDraf;
    CreateEmptyDraf(&stackDraf);

    // printWord(nama); printf("\n");
    // printWord(pass); printf("\n");
    // printWord(bio); printf("\n");
    // printWord(noHP); printf("\n");
    // printWord(weton); printf("\n");
    // printWord(jenis); printf("\n");
    printf("Nama: "); printWordNewline(nama);
    displayMatrixChar(profilepic);
    Pengguna user = {nama, pass, bio, noHP, weton, jenis, profilepic, friendreq, id, stackDraf};
    // PrintFoto(user);
    insertLastPengguna(&listUsers, user);
}

void BacaGrafPertemanan() {
    int n = listLengthPengguna(listUsers);
    readMatrixChar(&FriendGraph, n, n);

    // displayMatrixChar(FriendGraph);
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

    Balasan b = {-1, text, author, t};
    TreeBalasan tree = NewTreeBalasan(b, Nil_BALASAN);
    Kicauan k = {id, text, likes, author, t, tree};

    insertLastKicauan(&listKicauan, k);
}

void BacaBalasan() {
    // ID Kicauan
    ADVNEWLINE();
    int IDUtas = WordToInt(currentWord);

    // Jumlah Balasan
    ADVNEWLINE();
    int n = WordToInt(currentWord);

    int indexKicauan = indexOfKicauan(IDUtas);
    // Baca Balasan
    for (int i = 0; i < n; i++) {
        // ID Parent
        ADVWORD();
        int IDParent = WordToInt(currentWord);

        // ID Balasan
        ADVNEWLINE();
        int IDBalasan = WordToInt(currentWord);

        // Text
        ADVNEWLINE();
        Word text = currentWord;

        // Author
        ADVNEWLINE();
        Word author = currentWord;

        // Datetime
        DATETIME t = parseDATETIME();

        // Insert Balasan
        Balasan b = {IDBalasan, text, author, t};
        ELMT_Kicauan(listKicauan, indexKicauan).jumlahBalasan += 1;
        TreeBalasan tree = ELMT_Kicauan(listKicauan, indexKicauan).tree;

        insertTreeBalasan(tree, IDParent, b);
    }
}

Word ReverseWord(Word w) {
    int len = w.Length;

    Word result = w;
    for (int i = 1; i <= len; i++) {
        result.TabWord[i - 1] = w.TabWord[len - i];
    }
    return result;
}

void BacaKarakterTerakhir(Word w, Word* res, int* num) {
    int len = w.Length;

    Word rev = ReverseWord(w);
    Word revNum = rev;
    Word result = rev;
    
    int iNum = 0;
    int iWord = 0;
    boolean atNum = true;
    for (int i = 0; i < len; i++) {
        if ((rev.TabWord[i] == BLANK) && atNum) {
            atNum = false;
            revNum.Length = iNum;
        } else if (atNum) {
            iNum += 1;
        } else {
            result.TabWord[iWord] = rev.TabWord[i];
            iWord += 1;
        }
    }

    result.Length = iWord;
    *res = ReverseWord(result);
    *num = WordToInt(ReverseWord(revNum));
}

void BacaDraf() {
    // Nama dan Jumlah Draf
    ADVNEWLINE();

    Word Nama;
    int JumlahDraf;
    BacaKarakterTerakhir(currentWord, &Nama, &JumlahDraf);

    // Isi dan Tanggal
    int indexPengguna = indexOfUser(listUsers, Nama);
    Stack s = ELMTPengguna(listUsers, indexPengguna).StackDraf;
    
    for (int i = 0; i < JumlahDraf; i++) {
        // Isi Draf
        ADVNEWLINE();
        Word text = currentWord;

        // Datetime
        DATETIME time = parseDATETIME();

        // Create Kicauan
        int id = 0;
        int likes = 0;
        Balasan b = {-1, text, Nama, time};
        TreeBalasan tree = NewTreeBalasan(b, Nil_BALASAN);
        
        Kicauan k = {id, text, likes, Nama, time, tree};
        PushDraf(&s, k);
    }

    Stack rev = reverseStackDraf(s);
    ELMTPengguna(listUsers, indexPengguna).StackDraf = rev; 
}

void BacaUtas(int IDUtas) {
    // ID Kicauan
    ADVNEWLINE();
    int IDKicau = WordToInt(currentWord);

    // Jumlah Utas
    ADVNEWLINE();
    int n = WordToInt(currentWord);

    int indexKicauan = indexOfKicauan(IDKicau);
    Kicauan k = ELMT_Kicauan(listKicauan, indexKicauan);
    // Baca Utas
    for (int i = 0; i < n; i++) {
        // Text
        ADVNEWLINE();
        Word text = currentWord;

        // Author
        ADVNEWLINE();
        Word author = currentWord;

        // Datetime
        DATETIME time = parseDATETIME();

        // Add to database
        Address node = newNodeUtas(author, i + 1, time, text);

        insertLastUtas(&((&k)->nextUtas), node);
    }
    k.idUtas = IDUtas;
    ELMT_Kicauan(listKicauan, indexKicauan) = k;
}

void simpanDATETIME(FILE* file, DATETIME t) {
    // Day
    fprintf(file, "%02d/", t.DD);
    
    // Month
    fprintf(file, "%02d/", t.MM);
    
    // Year
    fprintf(file, "%02d ", t.YYYY);
    
    // Hour
    fprintf(file, "%02d:", t.T.HH);
    
    // Min
    fprintf(file, "%02d:", t.T.MM);
    
    // Sec
    fprintf(file, "%02d", t.T.SS);
}

void SimpanDataConfig(char* folderpath, int op, char* suffix) {
    // 1. Setup filepath string
    char filepath[80];
    concatStrings(folderpath, suffix, filepath);

    // 2. Run write functions
    switch (op) {
        case 2:
            SimpanKicauan(filepath);
            break;
        case 3:
            SimpanBalasan(filepath);
            break;
        case 4:
            SimpanDraf(filepath);
            break;
        case 5:
            SimpanUtas(filepath);
            break;
    }
}

void SimpanKicauan(char* filepath) {
    // 1. Open filepath kicauan.config
    FILE *configFile = fopen(filepath, "w");

    if (configFile == NULL) {
        perror("Unable to open config file.\n");
    }

    // 2. Write to file
    int n = listLengthKicauan(listKicauan);
    fprintf(configFile, "%d\n", n);

    for (int i = 0; i < n; i++) {
        Kicauan k = ELMT_Kicauan(listKicauan, i);
        fprintf(configFile, "%d", k.id); fprintf(configFile, "\n");
        WriteWord(configFile, k.text); fprintf(configFile, "\n");
        fprintf(configFile, "%d", k.likes); fprintf(configFile, "\n");
        WriteWord(configFile, k.author); fprintf(configFile, "\n");
        simpanDATETIME(configFile, k.datetime);
        if (i != (n - 1)) {
            fprintf(configFile, "\n");
        }
    }

    // 3. Close file
    fclose(configFile);
}

void SimpanBalasan(char* filepath) {
    // 1. Open filepath balasan.config
    FILE *configFile = fopen(filepath, "w");

    if (configFile == NULL) {
        perror("Unable to open config file.\n");
    }

    // 2. Write to file
    int count = hitungKicauanDenganBalasan();
    int n = listLengthKicauan(listKicauan);
    fprintf(configFile, "%d\n", count);

    int currentKicauan = 0;
    for (int i = 0; i < n; i++) {
        Kicauan k = ELMT_Kicauan(listKicauan, i);
        if (k.jumlahBalasan > 0) {
            if (currentKicauan > 0) {
                fprintf(configFile, "\n");
            }
            fprintf(configFile, "%d\n", k.id);
            fprintf(configFile, "%d", k.jumlahBalasan);
            SimpanTreeBalasan(configFile, k.tree);
            currentKicauan += 1;
        }
    }

    // 3. Close file
    fclose(configFile);
}

void SimpanTreeBalasan(FILE* file, TreeBalasan t) {
	if (t != Nil_BALASAN) {        
        int i = 0;
        while (i < TREECOUNT_BALASAN(t)) {
            Balasan parent = ROOT_BALASAN(t);
            Balasan child = ROOT_BALASAN(SUBTREE_BALASAN(t, i));

            fprintf(file, "\n%d %d\n", parent.id, child.id);
            WriteWord(file, child.text); fprintf(file, "\n");
            WriteWord(file, child.author); fprintf(file, "\n");
            simpanDATETIME(file, child.datetime);

            SimpanTreeBalasan(file, SUBTREE_BALASAN(t, i));
            i += 1;
        }
	}
}

void SimpanDraf(char* filepath) {
    // 1. Open filepath kicauan.config
    FILE *configFile = fopen(filepath, "w");

    if (configFile == NULL) {
        perror("Unable to open config file.\n");
    }

    // 2. Write to file
    int n = JumlahPenggunaDenganDraf();
    fprintf(configFile, "%d", n);

    int len = listLengthPengguna(listUsers);
    for (int i = 0; i < len; i++) {
        Pengguna p = ELMTPengguna(listUsers, i);
        if (!IsEmptyDraf(p.StackDraf)) {
            int depth = StackLengthDraf(p.StackDraf);
            fprintf(configFile, "\n");
            WriteWord(configFile, p.Nama); fprintf(configFile, " %d", depth);
            
            Stack drafts = p.StackDraf;
            Kicauan k;
            while (!IsEmptyDraf(drafts)) {
                fprintf(configFile, "\n");

                PopDraf(&drafts, &k);
                WriteWord(configFile, k.text); fprintf(configFile, "\n");
                simpanDATETIME(configFile, k.datetime);
            }
        }
    }
    // 3. Close file
    fclose(configFile);
}

void SimpanUtas(char* filepath) {
    // 1. Open filepath kicauan.config
    FILE *configFile = fopen(filepath, "w");

    if (configFile == NULL) {
        perror("Unable to open config file.\n");
    }

    // 2. Write to file
    int n = JumlahUtas;
    fprintf(configFile, "%d", n);

    int len = listLengthKicauan(listKicauan);
    for (int i = 0; i < len; i++) {
        Kicauan k = ELMT_Kicauan(listKicauan, i);

        if (k.nextUtas != NULL) {
            int id = k.id;
            int nUtas = lengthUtas(k.nextUtas);

            fprintf(configFile, "\n%d", id);
            fprintf(configFile, "\n%d", nUtas);

            Address p = k.nextUtas;
            while (p != NULL) {
                fprintf(configFile, "\n");
                WriteWord(configFile, p->text); fprintf(configFile, "\n"); 
                WriteWord(configFile, p->author); fprintf(configFile, "\n"); 
                simpanDATETIME(configFile, p->datetime); 
                p = NEXT(p);
            }
        }
    }
    // 3. Close file
    fclose(configFile);
}

// 1. Pengguna
int indexOfPengguna(Word nama) {
    int n = listLengthPengguna(listUsers);

    int index = -1;
    int i = 0;
    while (i < n && index == -1) {
        if (WordEqual(ELMTPengguna(listUsers, i).Nama, nama)) {
            index = i;
        } else {
            i += 1;
        }
    }
    return index;
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

void Muat() {
    
}

void Simpan() {
    // 1. Ask for foldername from user
    printf("\nMasukkan nama folder penyimpanan: \n");

    STARTSENTENCE();
    Word foldernameWord = currentWord;
    char* foldername = WordToStr(foldernameWord);

    char folderpath[50];
    char prefix[] = "./config/";
    concatStrings(prefix, foldername, folderpath);

    // 2. Create folder if it doesn't exist
    if (!directoryExists(folderpath)) {
        printf("Belum terdapat folder tersebut. Akan dilakukan pembuatan folder terlebih dahulu.\n");
        // mkdir(folderpath, 0777);

        printf("Mohon tunggu...\n1...\n2...\n3...\nFolder sudah berhasil dibuat.\n");
    }

    // 3. Run write functions
    printf("\nAnda akan melakukan penyimpanan di ");
    printWord(foldernameWord); printf(".\n\nMohon tunggu...\n1...\n2...\n3...\n\nPenyimpanan telah berhasil dilakukan!\n");

    SimpanDataConfig(folderpath, 2, "/kicauan.config");
    SimpanDataConfig(folderpath, 3, "/balasan.config");
    SimpanDataConfig(folderpath, 4, "/draf.config");
    SimpanDataConfig(folderpath, 5, "/utas.config");
}

// 2. Profil

void Ganti_Profil(){
    int id;
    if (!isLoggedIn){
        printf("Anda belum login! Masuk terlebih dahulu untuk mengganti profil\n");
    }else{
        id = indexOfUser(listUsers, currentUser.Nama);
        printf("\n| Nama: "); printWord(currentUser.Nama); printf("\n");
        printf("| Bio Akun: "); printWord(currentUser.Bio); printf("\n");
        printWord(currentUser.noHP);
        printf("| Weton: "); printWord(currentUser.Weton); printf("\n\n");
        Word weton[] = {{"Pahing", 6}, {"Kliwon", 6}, {"Wage", 6}, {"Pon",3}, {"Legi", 4}};
        Word empty = {';',1};
        boolean emptystring=false;

        boolean validbio=false;
        Word bio;
        while (!validbio)
        {
            printf("Masukkan Bio Akun:\n");
            STARTSENTENCE();

            bio = currentWord;
            if (currentWord.Length<=135){
                validbio=true;
                if (WordEqual(currentWord,empty)){
                    emptystring=true;
                }
            }
            if (!validbio){
                printf("\n");
                printf("Bio melebihi panjang maksimum karakter!\n");
                printf("\n");
            }
        }
        if (!emptystring){
            currentUser.Bio=bio;
        }
        printf("\n");
        /* code */
        
        emptystring=false;
        boolean validnr=false;
        while (!validnr)
        {
            printf("Masukkan No HP:\n");
            STARTSENTENCE();
            if (WordEqual(currentWord,empty)){
                emptystring=true;
                validnr=true;
            }
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
        if (!emptystring){
            currentUser.noHP= (currentWord);
        }
        printf("\n");

        emptystring=false;
        boolean validwt=false;
        while (!validwt)
        {
            printf("Masukkan Weton:\n");
            STARTSENTENCE();
            if (WordEqual(currentWord,empty)){
                emptystring=true;
                validwt=true;
            }

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
        if(!emptystring){
            currentUser.Weton=currentWord;
        }
        printf("Profil anda sudah berhasil diperbarui!\n\n");
        listUsers.contents[id]=currentUser;
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
    printf("\n| Nama: "); printWord(p.Nama); printf("\n");
    printf("| Bio Akun: "); printWord(p.Bio); printf("\n");
    printf("| No HP: "); printWord(p.noHP); printf("\n");
    printf("| Weton: "); printWord(p.Weton); printf("\n\n");
    printf("Foto profil akun "); printWord(p.Nama); printf("\n");
    PrintFoto(p); printf("\n");
}

void Lihat_Profil(){
    Pengguna user;
    Word Publik = {"Publik", 6};

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
                user = ELMTPengguna(listUsers, userIndex);
                if(WordEqual(user.JenisAkun, Publik)){
                    PrintProfil(user);
                }else{
                    if (IsTeman(currentUser.Nama, name)){
                        PrintProfil(user);
                    }else{
                        printf("\nWah, akun "); printWord(name);printf(" diprivat nih. ikuti dulu yuk untuk bisa melihat profil "); printWord(name); printf("!\n\n"); 
                    }
                }
            }
        }
    }
}

void Atur_Jenis_Akun(){
    int id;
    if (!isLoggedIn){
        printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
    }else{
        id = indexOfUser(listUsers, currentUser.Nama);
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
        listUsers.contents[id]=currentUser;
    }    
}

void Ubah_Foto_Profil(){
    if (!isLoggedIn){
        printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
    }else{
        int id = indexOfUser(listUsers,currentUser.Nama);
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
        listUsers.contents[id].FotoProfil=fotoprofil;
        printf("\n");
        printf("Foto profil anda sudah berhasil diganti!\n\n");
        PrintFoto(listUsers.contents[id]);
    }
}

// 3. Teman
boolean IsTeman(Word user1, Word user2) {
    int idx1 = indexOfUser(listUsers, user1);
    int idx2 = indexOfUser(listUsers, user2);

    return (ELMT_MATRIXCHAR(FriendGraph, idx1, idx2) == FRIEND_MARK);
}

int Jumlah_Teman(Word p) {
    int jumlahTeman = 0;
    for (int i = 0; i < listLengthPengguna(listUsers); i++) {
        ElTypePengguna el = ELMTPengguna(listUsers, i);
        if (IsTeman(p, el.Nama)) {
            if (!WordEqual(p, el.Nama)) {
                jumlahTeman++;
            }
        }
    }
    return jumlahTeman;
}

void Daftar_Teman(Pengguna p) {
    int jumlahTeman = 0;
    if (!isLoggedIn) {
        printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
    } else {
        printWord(p.Nama);
        jumlahTeman = Jumlah_Teman(p.Nama);
        if (jumlahTeman == 0) {
            printf(" belum mempunyai teman! Tambah teman terlebih dahulu!\n");
        }
        else {
            printf(" memiliki %d teman\nDaftar teman ", jumlahTeman);
            printWord(p.Nama);
            printf("\n");
            for (int i = 0; i < listLengthPengguna(listUsers); i++) {
                ElTypePengguna el = ELMTPengguna(listUsers, i);
                if (IsTeman(p.Nama, el.Nama)) {
                    if (!WordEqual(p.Nama, el.Nama)) {
                        printf("| ");
                        printWord(el.Nama);
                        printf("\n");
                    }
                }
            }
        }
    }
}

void Hapus_Teman(Pengguna p) {
    printf("Masukkan nama pengguna:\n");
    STARTSENTENCE();
    Word nama = currentWord;
    if (!IsTeman(p.Nama,nama)) {
        printWord(nama);
        printf(" bukan teman Anda.\n");
    } else {
        printf("Apakah anda yakin ingin menghapus ");
        printWord(nama); 
        printf(" dari daftar teman anda?(YA/TIDAK) ");
        STARTSENTENCE();
        Word choice = currentWord;
        if (choice.TabWord[0] == 'T') {
            printf("Penghapusan teman dibatalkan.\n");
        } else {
            ELMT_MATRIXCHAR(FriendGraph, indexOfUser(listUsers, p.Nama), indexOfUser(listUsers, nama)) = 0;
            printWord(nama);
            printf(" berhasil dihapus dari daftar teman Anda.\n");
        }
    }
}

// 4. Permintaan Pertemanan
void Make_Pqueue(PrioQueueChar p) {
    MakeEmpty_PQueue(&p, 20);
}

void Tambah_Teman(Pengguna p) {
    if (IsEmpty_PQueue(p.FriendReq)) {
        printf("Masukkan nama pengguna:\n");
        STARTSENTENCE();
        Word nama = currentWord;
        if (indexOfUser(listUsers, nama) == IDX_UNDEF_PENGGUNA) {
            printf("\nPengguna bernama ");
            printWord(nama);
            printf(" tidak ditemukan.\n");
        } else {
            printf("\nPermintaan pertemanan kepada ");
            printWord(nama);
            printf(" telah dikirim. Tunggu beberapa saat hingga permintaan Anda disetujui.\n");
            infotype_PQueue req = {Jumlah_Teman(p.Nama), p.Nama};
            Pengguna calon = ELMTPengguna(listUsers, indexOfPengguna(nama));
            Enqueue_PQueue(&calon.FriendReq, req);
        }
    } else {
        printf("Terdapat permintaan pertemanan yang belum Anda setujui. Silakan kosongkan daftar permintaan pertemanan untuk Anda terlebih dahulu.\n");
    }
}

void Daftar_Permintaan_Perteman(Pengguna p) {
    PrintPrioQueueChar_PQueue(&p.FriendReq);
}

void Setujui_Pertemanan(Pengguna p) {
    if (IsEmpty_PQueue(p.FriendReq)) {
        printf("Anda belum punya permintaan pertemanan.\n");
    } else {
        infotype_PQueue X;
        printf("Permintaan pertemanan teratas dari ");
        printWordNewline(Info_PQueue(Elmt_PQueue(p.FriendReq, Head_PQueue(p.FriendReq))));
        printf("| ");
        printWord(Info_PQueue(Elmt_PQueue(p.FriendReq, Head_PQueue(p.FriendReq))));
        printf("\n| Jumlah teman: %d\n", Prio_PQueue(Elmt_PQueue(p.FriendReq, Head_PQueue(p.FriendReq))));

        printf("Apakah Anda ingin menyetujui permintaan pertemanan ini? (YA/TIDAK) ");
        STARTSENTENCE();
        Word choice = currentWord;
        if (choice.TabWord[0] == 'Y') {
            ELMT_MATRIXCHAR(FriendGraph, indexOfUser(listUsers, p.Nama), indexOfUser(listUsers, Info_PQueue(Elmt_PQueue(p.FriendReq, Head_PQueue(p.FriendReq))))) = 1;
            printf("Permintaan pertemanan dari ");
            printWord(Info_PQueue(Elmt_PQueue(p.FriendReq, Head_PQueue(p.FriendReq))));
            printf(" telah disetujui. Selamat! Anda telah berteman dengan ");
            printWord(Info_PQueue(Elmt_PQueue(p.FriendReq, Head_PQueue(p.FriendReq))));
            printf(".\n");
            Dequeue_PQueue(&p.FriendReq, &X);
        } else {
            printf("Permintaan pertemanan dari ");
            printWord(Info_PQueue(Elmt_PQueue(p.FriendReq, Head_PQueue(p.FriendReq))));
            printf(" telah ditolak.\n");
            Dequeue_PQueue(&p.FriendReq, &X);
        }
    }
}

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

    printTab(1);
    printf("Balasan: %d\n", k.jumlahBalasan);
}

int indexOfKicauan(int id) {
    int n = listLengthKicauan(listKicauan);

    int index = -1;
    int i = 0;
    while (i < n && index == -1) {
        if (ELMT_Kicauan(listKicauan, i).id == id) {
            index = i;
        } else {
            i += 1;
        }
    }
    return index;
}

Kicauan inputKicau() {
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
        return inputKicau();
    } else {
        int id = listLengthKicauan(listKicauan) + 1;
        Word text = currentWord;
        int likes = 0;
        Word author = currentUser.Nama;
        DATETIME datetime = GetDateTime();

        Balasan b = {-1, text, author, datetime};
        TreeBalasan tree = NewTreeBalasan(b, Nil_BALASAN);
        Kicauan submittedKicauan = {id, text, likes, author, datetime, tree, 0};

        return submittedKicauan;
    }
}

void Kicau() {
    printf("Masukkan kicauan: \n");

    Kicauan submittedKicauan = inputKicau();

    printf("Selamat! kicauan telah diterbitkan!\nDetil kicauan:\n");
    PrintKicauan(submittedKicauan);

    insertLastKicauan(&listKicauan, submittedKicauan);
}

void DisplayKicauan() {
    int kicauanCount = listLengthKicauan(listKicauan);
    for (int i = (kicauanCount - 1); i >= 0; i--) {
        Kicauan k = ELMT_Kicauan(listKicauan, i);
        if (WordEqual(k.author, currentUser.Nama) || IsTeman(k.author, currentUser.Nama)) {
            PrintKicauan(k);
        }
    }
}

// 6. Balasan
int hitungKicauanDenganBalasan() {
    int n = listLengthKicauan(listKicauan);
    int count = 0;
    for (int i = 0; i < n; i++) {
        Kicauan k = ELMT_Kicauan(listKicauan, i);
        if (k.jumlahBalasan > 0) {
            count += 1;
        }
    }
    return count;
}

void PrintBalasan(Balasan k, int indent) {
    int id = k.id;
    Word text = k.text;
    Word author = k.author;
    DATETIME datetime = k.datetime;
    
    printf("\n");
    printTab(indent);
    printf("ID = %d\n", id);
    
    printTab(indent);
    printWordNewline(author);

    printTab(indent);
    TulisDATETIME(datetime);
    printf("\n");

    printTab(indent);
    printWordNewline(text);
}

void PrintTreeBalasan(TreeBalasan t, int indent) {
	if (t != Nil_BALASAN) {
		int i = 0;

        if (ROOT_BALASAN(t).id != IDX_UNDEF) {
            PrintBalasan(ROOT_BALASAN(t), indent);
        }
		while (i < TREECOUNT_BALASAN(t)) {
			PrintTreeBalasan(SUBTREE_BALASAN(t, i), indent + 1);
			i += 1;
		}
	}
}

void Balas() {
    ADVWORD();
    int IDUtas = WordToInt(currentWord);
    printf("IDUtas: %d\n", IDUtas);

    ADVWORD();
    int IDBalasan = WordToInt(currentWord);
    printf("IDBalasan: %d\n", IDBalasan);

    int indexKicauan = indexOfKicauan(IDUtas);
    if (indexKicauan == IDX_UNDEF_KICAUAN) {
        printf("Wah, tidak terdapat kicauan yang ingin Anda balas!\n");
    } else {
        TreeBalasan tree = ELMT_Kicauan(listKicauan, indexKicauan).tree;
        if (!treeExists(tree, IDBalasan)) {
            printf("Wah, tidak terdapat balasan yang ingin Anda balas!\n");
        } else {
            printf("Masukkan balasan: \n");

            Kicauan k = inputKicau();
            ELMT_Kicauan(listKicauan, indexKicauan).jumlahBalasan += 1;
            int id = ELMT_Kicauan(listKicauan, indexKicauan).jumlahBalasan;

            Balasan submittedBalasan = {id, k.text, k.author, k.datetime};
            insertTreeBalasan(tree, IDBalasan, submittedBalasan);

            printf("Selamat! Balasan telah diterbitkan!\nDetil balasan:\n");
            PrintBalasan(submittedBalasan, 1);
        }
    }
}

void DisplayBalasan() {
    ADVWORD();
    int IDUtas = WordToInt(currentWord);

    int indexKicauan = indexOfKicauan(IDUtas);
    if (indexKicauan == IDX_UNDEF_KICAUAN) {
        printf("Wah, tidak terdapat kicauan dengan ID tersebut!\n");
    } else if (ELMT_Kicauan(listKicauan, indexKicauan).jumlahBalasan == 0) {
        printf("Belum terdapat balasan apapun pada kicauan tersebut. Yuk balas kicauan tersebut!\n");
    } else {
        TreeBalasan tree = ELMT_Kicauan(listKicauan, indexKicauan).tree;
        PrintTreeBalasan(tree, 0);
    }
}

void HapusBalasan() {
    ADVWORD();
    int IDUtas = WordToInt(currentWord);
    printf("IDUtas: %d\n", IDUtas);

    ADVWORD();
    int IDBalasan = WordToInt(currentWord);
    printf("IDBalasan: %d\n", IDBalasan);

    int indexKicauan = indexOfKicauan(IDUtas);
    if (indexKicauan == IDX_UNDEF_KICAUAN) {
        printf("Wah, tidak terdapat balasan yang ingin Anda hapus!\n");
    } else {
        TreeBalasan tree = ELMT_Kicauan(listKicauan, indexKicauan).tree;
        if (!treeExists(tree, IDBalasan)) {
            printf("Wah, tidak terdapat balasan yang ingin Anda hapus!\n");
        } else {
            deleteTreeBalasan(&tree, IDBalasan);
            ELMT_Kicauan(listKicauan, indexKicauan).jumlahBalasan += -1;

            printf("Balasan berhasil dihapus! Semoga bukan balasan yang penting, yah!\n");
        }
    }
}

// 7. Draf Kicauan
int JumlahPenggunaDenganDraf() {
    int n = listLengthPengguna(listUsers);
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        Pengguna p = ELMTPengguna(listUsers, i);
        if (!IsEmptyDraf(p.StackDraf)) {
            count += 1;
        }
    }
    return count;
}

void BuatDraf(){ 
    printf("Masukkan draf:\n");
    Kicauan submittedDraf = inputKicau();
    printf("\n");
    ProsesDraf(submittedDraf);
}

void ProsesDraf(Kicauan Draf){
    printf("Apakah anda ingin menghapus, menyimpan, atau menerbitkan draf ini? (HAPUS / SIMPAN / TERBIT)\n");

    STARTSENTENCE();
    Word input = currentWord;

    Word HAPUS = {"HAPUS", 5};
    Word SIMPAN = {"SIMPAN", 6};
    Word TERBIT = {"TERBIT", 6};

    boolean inputValid = false;
    int userIndex = indexOfPengguna(currentUser.Nama);
    while (!inputValid) {        
        if(WordEqual(input, HAPUS)){
            printf("Draf telah berhasil dihapus!\n");
            inputValid = true;
        }else if(WordEqual(input, SIMPAN)){
            PushDraf(&currentUser.StackDraf, Draf);
            ELMTPengguna(listUsers, userIndex) = currentUser;

            printf("Draf telah berhasil disimpan!\n");
            inputValid = true;
        }else if (WordEqual(input, TERBIT)){
            printf("Selamat! Draf kicauan telah diterbitkan!\nDetil kicauan:\n");
            PrintKicauan(Draf);
            
            Draf.id = listLengthKicauan(listKicauan) + 1;
            insertLastKicauan(&listKicauan, Draf);
            inputValid = true;
        } else {
            printf("Masukkan tidak valid! Silahkan masukkan HAPUS, SIMPAN, atau TERBIT.\n");
        }
    }
}

void PrintDraf(Kicauan Draf){
    Word text = Draf.text;
    DATETIME datetime = Draf.datetime;

    printf("\n");
    printTab(1);
    TulisDATETIME(datetime);
    
    printf("\n");
    printTab(1);
    printWordNewline(text);
    printf("\n");
}

void LihatDraf(){
    if(IsEmptyDraf(currentUser.StackDraf)){
        printf("Yah, anda belum memiliki draf apapun! Buat dulu ya :D\n");
    }else{
        Kicauan k = InfoTop(currentUser.StackDraf);
        printf("Ini draf terakhir anda: \n");
        PrintDraf(k);

        Word HAPUS = {"HAPUS", 5};
        Word UBAH = {"UBAH", 4};
        Word TERBIT = {"TERBIT", 6};
        Word KEMBALI = {"KEMBALI", 7};

        Kicauan temp;
        boolean inputValid = false;

        int indexUser = indexOfPengguna(currentUser.Nama);
        while(!inputValid) {
            printf("Apakah anda ingin mengubah, menghapus, atau menerbitkan draf ini? (HAPUS / UBAH / TERBIT / KEMBALI)\n");

            STARTSENTENCE();
            Word input = currentWord;
            if(WordEqual(input, HAPUS)){
                PopDraf(&currentUser.StackDraf, &temp);
                ELMTPengguna(listUsers, indexUser) = currentUser;

                printf("Draf telah berhasil dihapus!\n");
                inputValid = true;
            }else if(WordEqual(input, UBAH)){
                PopDraf(&currentUser.StackDraf, &temp);
                ELMTPengguna(listUsers, indexUser) = currentUser;

                printf("Masukkan draf yang baru: \n");
                Kicauan submittedDraf = inputKicau();
                printf("\n");
                ProsesDraf(submittedDraf);
                inputValid = true;
            } else if (WordEqual(input, TERBIT)) {
                PopDraf(&currentUser.StackDraf, &k);
                ELMTPengguna(listUsers, indexUser) = currentUser;
                k.id = listLengthKicauan(listKicauan) + 1;
                insertLastKicauan(&listKicauan, k);

                printf("Selamat! Draf kicauan telah diterbitkan!\nDetil kicauan:\n");
                PrintKicauan(k);
                inputValid = true;
            } else if (WordEqual(input, KEMBALI)) {
                printf("Modifikasi draf dibatalkan. Kembali ke menu!\n");
                inputValid = true;
            } else{
                printf("Perintah tidak valid! Masukkan HAPUS, UBAH, TERBIT, atau KEMBALI.\n");
            }
        }
    }
}

// 8. Utas
Kicauan KicauandenganIdUtas (int IDUtas)
/*Mengirim Kicauan dengan IDUtas yang sama*/
/*Pre kondisi pasti ada kicau dengan IDUtas*/
{
    int n = listLengthKicauan(listKicauan);
    for(int i = 0; i < n; i++) {
        if(ELMT_Kicauan(listKicauan, i).idUtas == IDUtas){
            return ELMT_Kicauan(listKicauan, i);
        }
    }
}

void printUtas(Kicauan k)
// void printInfo(List l);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    Address p = k.nextUtas;
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
    
    while (p != NULL){
        int index = INDEX(p);
        Word author = AUTHOR(p);
        DATETIME datetime = DATETIME(p);
        Word text = TEXT(p);
        
        printf("\n");
        printTab(2);
        printf("INDEX = %d\n", index);
        
        printTab(2);
        printWordNewline(author);

        printTab(2);
        TulisDATETIME(datetime);
        printf("\n");

        printTab(2);
        printWordNewline(text);
        p = NEXT(p);
    }
}

Address inputUtas(){
    printf("\nMasukkan kicauan: \n");
    Kicauan k = inputKicau();
    Address u = newNodeUtas(k.author, JumlahUtas, k.datetime, k.text);
    return u;
}

void Utas(){
    ADVWORD();
    int IDKicau = WordToInt(currentWord);
    int indexKicauan = indexOfKicauan(IDKicau);
    
    if (indexKicauan == IDX_UNDEF_KICAUAN) {
        printf("Kicauan tidak ditemukan!\n");
    }else{
        // Compare Username dengan author
        Kicauan k = ELMT_Kicauan(listKicauan, indexKicauan);
        JumlahUtas++;
        k.idUtas = JumlahUtas;
        Word author = k.author;
        if (!WordEqual(author,currentUser.Nama)){
            printf("Utas ini bukan milik anda\n");
        }else{
            printf("Utas berhasil dibuat!\n");
            Address p = inputUtas();
            p->index = lengthUtas((&k)->nextUtas) + 1;

            insertLastUtas(&((&k)->nextUtas), p);
            
            // Melakukan lanjutan utas
            printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK): ");
            // Asumsi yang di input selalu benar
            STARTSENTENCE();
            Word YA = {"YA", 2};
            Word TIDAK = {"TIDAK", 5};
            while (WordEqual(currentWord,YA))
            {
                Address p = inputUtas();
                p->index = lengthUtas((&k)->nextUtas) + 1;

                insertLastUtas(&((&k)->nextUtas), p);
                printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK): ");
                STARTSENTENCE();
            }
            printf("\nUtas selesai!");
            ELMT_Kicauan(listKicauan, indexKicauan) = k;
        }
    }
}

void SambungUtas(){
    ADVWORD();
    int IDUtas = WordToInt(currentWord);
    ADVWORD();
    int index = WordToInt(currentWord);
    if(IDUtas > JumlahUtas || IDUtas <= 0){
        printf("Utas tidak ditemukan!\n");
    }else{
        Kicauan k = KicauandenganIdUtas(IDUtas);
        int indexKicauan = indexOfKicauan(k.id);

        Pengguna p = currentUser;
        Word author = k.author;
        Word Username = p.Nama;
        if(index > (lengthUtas((&k)->nextUtas) + 1)){
            printf("Index terlalu tinggi!\n");
        }else{
            if (!WordEqual(author,Username)){
                printf("Utas ini bukan milik anda\n");
            }else{
                Address p = inputUtas();
                if (index == (lengthUtas((&k)->nextUtas) + 1)) {
                    insertLastUtas(&((&k)->nextUtas), p);
                } else {
                    insertAtUtas(&((&k)->nextUtas), p, index);
                }

                ELMT_Kicauan(listKicauan, indexKicauan) = k;
                printf("Utas berhasil disambung!\n");
            }
        }
    }
}

void HapusUtas(){
    ADVWORD();
    int IDUtas = WordToInt(currentWord);
    ADVWORD();
    int index = WordToInt(currentWord);
    if(IDUtas>JumlahUtas || IDUtas <= 0){
        printf("Utas tidak ditemukan!\n");
    }else{
        Kicauan k = KicauandenganIdUtas(IDUtas);
        int indexKicauan = indexOfKicauan(k.id);

        Pengguna p = currentUser;
        Word author = k.author;
        Word Username = p.Nama;
        if(index>lengthUtas((&k)->nextUtas)){
            printf("Kicauan sambungan dengan index %d tidak ditemukan pada utas!\n", index);
        }else if(index == 0){
            printf("Anda tidak bisa menghapus kicauan utama!\n");    
        }else{
            if (!WordEqual(author,Username)){
                printf("Anda tidak bisa menghapus kicauan dalam utas ini!\n");
            }else{
                deleteAtUtas(&((&k)->nextUtas), index);

                ELMT_Kicauan(listKicauan, indexKicauan) = k;
                printf("Kicauan sambungan berhasil dihapus!\n");
            }
        }
    }
}

void CetakUtas(){
    ADVWORD();
    int IDUtas = WordToInt(currentWord);
    Word privat = {"Privat", 6};
    Word publik = {"Publik", 6};
    if(IDUtas>JumlahUtas || IDUtas <= 0){
        printf("Utas tidak ditemukan!\n");
    } else {
        Kicauan k = KicauandenganIdUtas(IDUtas);
        List l = k.nextUtas;
        Word authorUtas = k.author;
        int authorIndex = indexOfPengguna(k.author);
        Word authorStatus = ELMTPengguna(listUsers, authorIndex).JenisAkun;

        if (WordEqual(authorStatus, privat) && !IsTeman(authorUtas, currentUser.Nama) && !WordEqual(authorUtas, currentUser.Nama)){
            printf("Akun yang membuat utas ini adalah akun privat! Ikuti dahulu akun ini untuk melihat utasnya!\n");
        }else {
            printUtas(k);
        }
    }
}

// 9. Tagar

// 10. Kelompok Teman
void KelompokTeman() {
    int n = ROW_EFF_MATRIXCHAR(FriendGraph);
    DisjointSet groups = findGroups(FriendGraph);
    DisjointSet groupList = groups;

    int count = 0;
    for (int i = 0; i < listLength(groups); i++) {
        if (getIndexRoot(groups, i) == getIndexRoot(groups, currentUser.id)) {
            ELMT(groupList, i) = 1;
            count += 1;
        } else {
            ELMT(groupList, i) = 0;
        }
    }
    printf("Terdapat %d orang dalam Kelompok Teman ", count);
    printWord(currentUser.Nama);
    printf(": \n");

    int pre = 1;
    for (int i = 0; i < listLength(groupList); i++) {
        if (ELMT(groupList, i) == 1) {
            printf("%d. ", pre);
            pre += 1;
            printWord(ELMTPengguna(listUsers, i).Nama);
            printf("\n");
        } 
    }
}

// 11. FYB
void FYB() {
    int n = listLengthKicauan(listKicauan);
    n = (n < 8) ? n : 8;

    printf("Berikut %d kicauan dengan jumlah like tertinggi di FYB: \n", n);
    MaxHeapKicauan h = createMaxHeapKicauan(listKicauan);
    HeapifyListKicauan(&h);

    for (int i = 0; i < n; i++) {
        printf("\nKicauan %d: ", (i + 1));
        ElTypeKicauan root;
        PopMaxHeap(&h, &root);

        PrintKicauan(root);
    }
}