#include <stdio.h>
#include "disjointset.h"
#include "../wordmachine/charmachine.h"
#include "../wordmachine/wordmachine.h"

int main() {
    // STARTFILE("./modules/disjointset/disjoint2.txt");

    MatrixChar m;
    // readMatrixChar(&m, 10, 10);
    DisjointSet s = createDisjointSet(4);
    ELMT(s, 0) = -3;
    ELMT(s, 1) = -1;
    ELMT(s, 2) = 0;
    ELMT(s, 3) = 0;
    // ELMT(s, 4) = 0;
    // ELMT(s, 5) = -3;
    // ELMT(s, 6) = 5;
    // ELMT(s, 7) = 5;
    // ELMT(s, 8) = -2;
    // ELMT(s, 9) = 8;

    printList(s); printf("\n");
    // printf("2--> %d\n", PARENT(s, 2));
    for (int i = 0; i < 4; i++) {
        printf("%d--> %d\n", i, getIndexRoot(s, i));
    }

    // displayMatrixChar(m);
    // DisjointSet groups = findGroups(m);
    // printList(groups);

    return 0;
}