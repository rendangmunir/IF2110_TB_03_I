#include <stdio.h>
#include "charmachine.h"
#include "wordmachine.h"

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

int main() {
    STARTSENTENCE();

    Word w = currentWord;
    Word name;
    int num;

    BacaKarakterTerakhir(w, &name, &num);
    printWordNewline(name);
    printf("Angka: %d\n", num);
    return 0;
}