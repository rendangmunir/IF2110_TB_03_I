#include <stdio.h>
#include "tree.h"

int main() {
    Tree t = NewTree(1, Nil);

    insertTree(t, 1, 2);
    insertTree(t, 1, 3);
    insertTree(t, 2, 4);
    insertTree(t, 4, 6969);

    deleteTree(&t, 3);
    PrintTree(t);

    return 0;
}