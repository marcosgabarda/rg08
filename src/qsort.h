#ifndef _QSORT_
#define _QSORT_

#include "types.h"
#include "node.h"

int particion( Node **frecuencias, int izquierda, int derecha );
void _quicksort( Node **frecuencias, int first, int last );
vector<Node *> qsort (vector<Node *> fuente) ;

#endif
