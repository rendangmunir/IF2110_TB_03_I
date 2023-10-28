#ifndef MAXHEAPKICAUAN_H
#define MAXHEAPKICAUAN_H

#include "boolean.h"
#include "../listdinkicauan/listdinkicauan.h"

// Definisi Heap
typedef ListDinKicauan MaxHeapKicauan;

#define ELMT_Heap(l, i) ELMT_Kicauan(l, i)
#define ROOT_Heap(l) ELMT_Kicauan(l, 1)
#define LEFTCHILD_Heap(i) (2 * i)
#define RIGHTCHILD_Heap(i) ((2 * i) + 1)

/* ********** KONSTRUKTOR ********** */
MaxHeapKicauan createMaxHeapKicauan(ListDinKicauan h);

void dealocateMaxHeapKicauan(MaxHeapKicauan *h);

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int MaxHeapLengthKicauan(MaxHeapKicauan h);

int swapMaxHeap(MaxHeapKicauan *h, int i, int j);

// Operasi Max Heap
void HeapifyListKicauan(MaxHeapKicauan *h);

void Heapify(MaxHeapKicauan *h, int index);

void PopMaxHeap(MaxHeapKicauan *h, ElTypeKicauan *root);

#endif