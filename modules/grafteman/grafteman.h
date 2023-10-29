/**** Definisi Type GrafTeman dengan representasi Adjacency Matrix dan ElType char ****/

#include "../matrixchar/matrixchar.h"

#ifndef GRAFTEMAN_H
#define GRAFTEMAN_H

#define FRIEND_MARK '1'
#define NOTFRIEND_MARK '0'

typedef MatrixChar GrafTeman;

/**** Konstruktor ****/
GrafTeman createGrafTeman(int users);

#endif