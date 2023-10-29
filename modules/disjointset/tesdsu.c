#include <stdio.h>
#include "disjointset.h"
#include "../wordmachine/charmachine.h"
#include "../wordmachine/wordmachine.h"

int main() {
    STARTFILE("./modules/disjointset/disjoint2.txt");

    MatrixChar m;
    readMatrixChar(&m, 10, 10);
    DisjointSet s = createDisjointSet(10);
    // ELMT(s, 0) = -4;
    // ELMT(s, 1) = 0;
    // ELMT(s, 2) = -1;
    // ELMT(s, 3) = 0;
    // ELMT(s, 4) = 0;
    // ELMT(s, 5) = -3;
    // ELMT(s, 6) = 5;
    // ELMT(s, 7) = 5;
    // ELMT(s, 8) = -2;
    // ELMT(s, 9) = 8;

    // printList(s); printf("\n");

    // printf("3--> %d\n", PARENT(s, 3));

    displayMatrixChar(m);
    DisjointSet groups = findGroups(m);
    printList(groups);

    return 0;
}