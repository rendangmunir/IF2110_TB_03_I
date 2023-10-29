/**** Definisi Type Disjoint Set Union (DSU) representasi array statik dan berelemen integer ****/

#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#define PARENT(s, i) (ELMT(s, i))

#include "../liststatik/liststatik.h"
#include "../matrixchar/matrixchar.h"
#include "../grafteman/grafteman.h"

typedef ListStatik DisjointSet;

/**** Konstruktor ****/
DisjointSet createDisjointSet(int length);

/**** Getter ****/
int getIndexRoot(DisjointSet s,  int i);

/**** Setter ****/
void UnionDisjointSet(DisjointSet *s, int i, int j);

DisjointSet findGroups(GrafTeman m);

#endif