#include "prioqueuechar.h"

boolean IsEmpty (PrioQueueChar Q)
{
    return(Head(Q) == Nil && Tail(Q) == Nil); 
}

//boolean IsFull (PrioQueueChar Q)

int NBElmt (PrioQueueChar Q)
{
    if (IsEmpty(Q)) {
        return 0;
    }
    else {
        if (Tail(Q) >= Head(Q)) {
            return(Tail(Q) - Head(Q) + 1);
        }
        else {
            int temp = MaxEl(Q) + Tail(Q);
            return(temp - Head(Q) + 1);
        }
    }
}

/*
void MakeEmpty (PrioQueueChar * Q, int Max)
{
    (*Q).T = (GrafTeman *) malloc((Max) * sizeof(GrafTeman));
    if ((*Q).T == NULL) {
        MaxEl_PQueue(*Q) = 0;
    }
    else {
        Head_PQueue(*Q) = Nil;
        Tail_PQueue(*Q) = Nil;
        MaxEl_PQueue(*Q) = Max;
    }
}
*/

void DeAlokasi(PrioQueueChar * Q)
{
    Head_PQueue(*Q) = Nil;
    Tail_PQueue(*Q) = Nil;
    MaxEl_PQueue(*Q) = 0;
    free((*Q).T);
}

void Enqueue (PrioQueueChar * Q, infotype X)
{
    boolean found;
    int idx;
    int i, j;
    //food temp;

    // enqueue based on most popular
    if (IsEmpty(*Q)){
            Head_PQueue(*Q) = 0;
            Tail_PQueue(*Q) = 0;
            InfoHead_PQueue(*Q) = X;
    }
    else {
        
    }
}