#include <stdio.h>
#include "tree.h"

int main() {
    Tree t = NewTree(1, Nil);

    Tree c2 = NewTree(2, Nil);
    Tree c3 = NewTree(3, Nil);
    Tree c4 = NewTree(4, Nil);

    ConnectChild(c2, &t);
    ConnectChild(c3, &t);
    ConnectChild(c4, &t);

    // for (int i = 0; i < 3; i++) {
    //     if (ROOT(SUBTREE(t, i)) == 3) {
    //         printf("Success");
    //         SUBTREE(t, i) = Nil;
    //     }
    // }

    // PrintTree(t);

    Tree c69 = NewTree(69, Nil);
    Tree c6969 = NewTree(6969, Nil);
    ConnectChild(c69, &c4);
    ConnectChild(c6969, &c4);

    ConnectChild(c3, &c2);
    ConnectChild(c4, &c2);

    ConnectChild(c2, &t);

    Tree c5 = NewTree(5, Nil);
    Tree c6 = NewTree(6, Nil);

    ConnectChild(c6, &c5);

    ConnectChild(c5, &t);

    PrintTree(t);
    printf("\n");

    // boolean found = false;
    // Tree res = Nil;
    // searchTree(t, 4, &found, &res);

    Tree *res = searchTree(t, 2);
    Tree r = *res;
    res = Nil;
    
    // Tree c42069 = NewTree(42069, Nil);
    // ConnectChild(c42069, res);

    printf("\n");
    PrintTree(r);

    printf("\n");
    PrintTree(t);

    return 0;
}