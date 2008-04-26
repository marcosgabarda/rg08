#include "types.h"
#include "qsort.h"

int particion( Node **frecuencias, int izquierda, int derecha )
{
  int posicion = izquierda;
  while ( true ) {
    while ( frecuencias[ posicion ]->getProb() <= frecuencias[ derecha ]->getProb() && posicion != derecha )
      --derecha;
    if ( posicion == derecha )
      return posicion;
    if ( frecuencias[ posicion ]->getProb() > frecuencias[ derecha ]->getProb()) {

      Node *temp;
      temp = frecuencias[ posicion ];
      frecuencias[ posicion ] = frecuencias[ derecha ];
      frecuencias[ derecha ] = temp;

      posicion = derecha;
    }
    while ( frecuencias[ izquierda ]->getProb() <= frecuencias[ posicion ]->getProb() && izquierda != posicion )
      ++izquierda;
    if ( posicion == izquierda )
      return posicion;
    if ( frecuencias[ izquierda ]->getProb() > frecuencias[ posicion ]->getProb() ) {

      Node *temp;
      temp = frecuencias[ posicion ];
      frecuencias[ posicion ] = frecuencias[ izquierda ];
      frecuencias[ izquierda ] = temp;

      posicion = izquierda;
    }
  }
}

void _quicksort( Node **frecuencias, int first, int last )
{
  int posicionActual;
  if ( first >= last )
    return;
  posicionActual = particion( frecuencias, first, last );
  _quicksort( frecuencias, first, posicionActual - 1 );   
  _quicksort( frecuencias, posicionActual + 1, last );    
}


vector<Node *> qsort (vector<Node *> fuente) {

  
  Node **_fuente = new Node *[fuente.size()];
  vector<Node *> _fuente_ordenada (fuente.size());

  for (unsigned int i = 0; i < fuente.size(); i++) {
    _fuente[i] = fuente[i];
  }

  _quicksort (_fuente, 0, fuente.size() - 1);  

  for (unsigned int i = 0; i < fuente.size(); i++) {
    _fuente_ordenada[i] = _fuente[i];
  }

  delete[] _fuente;

  return _fuente_ordenada;

}
