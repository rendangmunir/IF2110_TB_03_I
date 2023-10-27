#include <stdio.h>
#include "charmachine.h"
#include "wordmachine.h"

Word currentWord;
boolean EndWord;

void IgnoreBlanks() { 
    /* Mengabaikan satu atau beberapa BLANK
    I.S. : currentChar sembarang
    F.S. : currentChar ≠ BLANK atau currentChar = MARK */
    while (currentChar == BLANK && currentChar != MARK) {
        ADV();
    }
}

void IgnoreEnters() {
    while (currentChar == ENTER) {
        ADV();
    }
}

void IgnoreR() {
    while (currentChar == '\r') {
        ADV();
    }
}

void STARTWORD() { 
    /* I.S. : currentChar sembarang
    F.S. : EndWord = true, dan currentChar = MARK;
            atau EndWord = false, currentWord adalah kata yang sudah diakuisisi,
            currentChar karakter pertama sesudah karakter terakhir kata */    
    START();
    IgnoreBlanks();
    IgnoreEnters();
    if (currentChar == MARK) {
        EndWord = true;
    } else {
        EndWord = false;
        CopyWord();
    }

}

void STARTSENTENCE() {
    START();
    IgnoreEnters();

    int i = 0;
    while (currentChar != MARK && i < NMax) {
        currentWord.TabWord[i] = currentChar;
        ADV();
        i += 1;
    }
    currentWord.Length = i;
}

void ADVWORD() { 
    /* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
    F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
            currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
            Jika currentChar = MARK, EndWord = true.
    Proses : Akuisisi kata menggunakan procedure SalinWord */
    IgnoreBlanks();
    if (currentChar == MARK) {
        EndWord = true;
    } else {
        CopyWord();
        IgnoreBlanks();
    }
}

void CopyWord() { 
    /* Mengakuisisi kata, menyimpan dalam currentWord
    I.S. : currentChar adalah karakter pertama dari kata
    F.S. : currentWord berisi kata yang sudah diakuisisi;
            currentChar = BLANK atau currentChar = MARK;
            currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
            Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
    int i = 0;
    while ((currentChar != MARK) && (currentChar != BLANK)) {
        currentWord.TabWord[i] = currentChar;
        ADV();
        i++;
    }
    if (i < NMax) {
        currentWord.Length = i;
    } else {
        currentWord.Length = NMax;
    }
}

// 1 - WordEqual
boolean WordEqual(Word a, Word b) {
    if (a.Length != b.Length) {
        return false;
    } else {
        int n = a.Length;

        boolean equal = true;
        int i = 0;
        while (equal && (i < n)) {
            if ((a.TabWord[i] != b.TabWord[i])) {
                equal = false;
            } else {
                i += 1;
            }
        }

        return equal;
    }
}

// 2 - PrintWord
void printWord(Word w) {
    int i;
    for (i = 0; i < w.Length; i++) {
        printf("%c", w.TabWord[i]);
    }
}

// 3 - printWordNewline
void printWordNewline(Word w) {
    printWord(w);
    printf("\n");
}

// 4 - ADVNEWLINE
void ADVNEWLINE() {
    IgnoreEnters();
    
    int i = 0;
    while (currentChar != ENTER && currentChar != '\r') {
        currentWord.TabWord[i] = currentChar;
        i += 1;
        ADV();
    }
    IgnoreR();

    currentWord.Length = (i < NMax) ? i : NMax;
}

// 5 - StrToInt
int WordToInt(Word w) {
    int mult = w.Length - 1;

    int i, j;
    int dec;
    int sum = 0;
    for (i = 0; i < w.Length; i++) {
        dec = 1;
        for (j = mult; j > i; j--) {
            dec *= 10;
        }
        sum += (w.TabWord[i] - 48) * dec;
    }

    return sum;
}