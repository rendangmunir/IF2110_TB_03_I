#include <stdio.h>
#include "stackDraf.h"

void CreateEmptyDraf(Stack *S)
{
    Top(*S) = Nil;
}

boolean IsEmptyDraf(Stack S){
    return Top(S) == Nil;
}

boolean IsFullDraf(Stack S){
    return Top(S) == MaxEl - 1;
}

void PushDraf(Stack *S, infotype X){
    Top(*S)++;
    InfoTop(*S) = X;
}

void PopDraf(Stack *S, infotype* X){
    *X = InfoTop(*S);
    Top(*S)--;
}

int StackLengthDraf(Stack s) {
    Stack copy = s;

    int count = 0;
    infotype temp;
    while (!IsEmptyDraf(copy)) {
        count += 1;
        PopDraf(&copy, &temp);
    }

    return count;
}

Stack reverseStackDraf(Stack s) {
    Stack rev;
    CreateEmptyDraf(&rev);

    Stack copy = s;
    Kicauan k;
    while (!IsEmptyDraf(copy)) {
        PopDraf(&copy, &k);
        PushDraf(&rev, k);
    }

    return rev;
}