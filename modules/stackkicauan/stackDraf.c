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
