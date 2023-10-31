#include <stdio.h>
#include <stdlib.h>

#include "maxheapkicauan.h"

/* ********** KONSTRUKTOR ********** */
MaxHeapKicauan createMaxHeapKicauan(ListDinKicauan l) {
    MaxHeapKicauan h;
    int length = listLengthKicauan(l);
    int capacity = l.capacity;
    CreateListDinKicauan(&h, capacity + 1);

    int n = 0;
    for (int i = 0; i < length; i++) {
        ELMT_Kicauan(h, (i + 1)) = ELMT_Kicauan(l, i);
        n = i;
    }

    h.nEff = n + 2;
    return h;
}

void dealocateMaxHeapKicauan(MaxHeapKicauan *h) {
    h->capacity = 0;
    h->nEff = 0;
    free(h->buffer);
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int MaxHeapLengthKicauan(MaxHeapKicauan h) {
    return h.nEff;
}

int swapMaxHeap(MaxHeapKicauan *h, int i, int j) {
    ElTypeKicauan temp = ELMT_Heap(*h, i);
    ELMT_Heap(*h, i) = ELMT_Heap(*h, j);
    ELMT_Heap(*h, j) = temp;
}

// Operasi Max Heap
void HeapifyListKicauan(MaxHeapKicauan *h) {
    int length = MaxHeapLengthKicauan(*h);

    for (int i = length / 2; i > 0; i--) {
        Heapify(h, i);
    }
}

void Heapify(MaxHeapKicauan *h, int index) {
    // 1. Get left child and right child index
    int l = LEFTCHILD_Heap(index);
    int r = RIGHTCHILD_Heap(index);
    int length = MaxHeapLengthKicauan(*h);

    if (l < length) {
        int leftchild = ELMT_Heap(*h, l).likes;
        DATETIME leftDATETIME = ELMT_Heap(*h, l).datetime;
        
        int largest = index;
        int largestlikes = ELMT_Heap(*h, largest).likes;
        DATETIME largestDATETIME = ELMT_Heap(*h, largest).datetime;

        // Compare current and leftchild
        boolean leftLargerLikes = (leftchild > largestlikes);
        boolean leftSmallerDATETIME = (leftchild == largestlikes) && (DLT(leftDATETIME, largestDATETIME)); 
        if (l < length && (leftLargerLikes || leftSmallerDATETIME)) {
            largest = l;
            largestlikes = ELMT_Heap(*h, largest).likes;
            largestDATETIME = leftDATETIME;
        }

        if (r < length) {
            int rightchild = ELMT_Heap(*h, r).likes;
            DATETIME rightDATETIME = ELMT_Heap(*h, r).datetime;

            // Compare largest and rightchild
            boolean rightLargerLikes = (rightchild > largestlikes);
            boolean rightSmallerDATETIME = (rightchild == largestlikes) && (DLT(rightDATETIME, largestDATETIME)); 
            if (r < length && (rightLargerLikes || rightSmallerDATETIME)) {
                largest = r;
                largestlikes = ELMT_Heap(*h, largest).likes;
                largestDATETIME = rightDATETIME;
            }
        }

        if (largest != index) {
            swapMaxHeap(h, index, largest);
            Heapify(h, largest);
        }
    }
}

void PopMaxHeap(MaxHeapKicauan *h, ElTypeKicauan *root) {
    *root = ROOT_Heap(*h);
    swapMaxHeap(h, 1, (MaxHeapLengthKicauan(*h) - 1));

    h->nEff += -1;
    Heapify(h, 1);
}