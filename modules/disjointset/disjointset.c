#include <stdio.h>

#include "disjointset.h"

/**** Konstruktor ****/
DisjointSet createDisjointSet(int length) {
    DisjointSet s;
    CreateListStatik(&s);

    for (int i = 0; i < length; i++) {
        ELMT(s, i) = -1;
    }
    return s;
}

/**** Getter ****/
int getIndexRoot(DisjointSet s,  int i) {
    while (ELMT(s, i) >= 0) {
        i = PARENT(s, i);
    }
    return i;
}

/**** Setter ****/
void UnionDisjointSet(DisjointSet *s, int a, int b) {
    int rootA = getIndexRoot(*s, a);
    int rootB = getIndexRoot(*s, b);

    boolean sameSet = (rootA == rootB);
    if (!sameSet) {
        if (ELMT(*s, rootA) <= ELMT(*s, rootB)) {
            ELMT(*s, rootA) += -1;
            ELMT(*s, rootB) = rootA;
        } else {
            ELMT(*s, rootA) = rootB;
            ELMT(*s, rootB) += -1;
        }
    }
}

DisjointSet findGroups(GrafTeman m) {
    if (ROW_EFF_MATRIXCHAR(m) == COL_EFF_MATRIXCHAR(m)) {
        int n = ROW_EFF_MATRIXCHAR(m);

        DisjointSet s = createDisjointSet(n);
        for (int i = 0; i < n; i++) {
            for (int j = (i + 1); j < n; j++) {
                if (ELMT_MATRIXCHAR(m, i, j) == '1') {
                    UnionDisjointSet(&s, i, j);
                }
            }
        }
        return s;
    }
}