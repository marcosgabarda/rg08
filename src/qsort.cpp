#include "types.h"
#include "qsort.h"


/**
 * Funci&oacute;n particion que se usa en el algoritmo de QuickSort. Est&aacute; implementado
 * para funcionar con vecotres de &aacute;rboles de codificaci&oacute;n Huffman.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] frecuencias Vector de punteros a Node.
 * \param[in] izquierda L&iacute;mite izquierdo.
 * \param[in] derecha L&iacute;mite derecho.
 * \return Posici&oacute; que marca la partici&oacute;n.
 */
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

/**
 * Algoritmo de QuicSort.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in,out] frecuencias Vector de punteros a Node que se ha de ordenar.
 * \param[in] first Priemera posici&oacute;n del vector que se tiene que ordenar.
 * \param[in] last &Uacute;ltima posici&oacute;n del vector que se tiene que ordenar.
 */

void _quicksort( Node **frecuencias, int first, int last )
{
  int posicionActual;
  if ( first >= last )
    return;
  posicionActual = particion( frecuencias, first, last );
  _quicksort( frecuencias, first, posicionActual - 1 );   
  _quicksort( frecuencias, posicionActual + 1, last );    
}

/**
 * Funci&oacute;n que encapsula la llamada al algoritmo de QuickSort.
 *
 * \param fuente Vector de punteros a nodos para ordenar.
 * \return Vector ordenado.
 */
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
