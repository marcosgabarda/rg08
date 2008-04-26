#include "types.h"
#include "huffman.h"
#include "qsort.h"

Huffman::Huffman (FMN Origen) {
  
  vector<Node *> vFuente(Origen.size());
  int i = 0;
  for (  FMN::iterator it = Origen.begin(); it != Origen.end(); it++, i++) {
    Node *Leaf = new Node(it->first, it->second);
    vFuente[i] = Leaf;
  }
  m_vFuente = vFuente;
  
}

/**
 * Contruimos el arbol de forma recursiva. Dentro de un vector de árboles,
 * seleccionamos los dos con una menor frecuencia, y los fusionamos, 
 * dando a la raiz del nuevo arbol la frecuencia suma de las hojas:
 * 
 *                                       (f1+f2)
 *                                        /  \
 *               (a,f1)   (b,f2)   =>   (a)  (b) 
 *
 * Siendo f1, y f2 las menores frecuencias.
 * Se actualiza el vector, y se realiza la llamada recursiva. El 
 * procedimiento termina cuando solo nos queda un arbol, que corresponde
 * al arbol final.
 *
 * \author Iván Rodriguez Sastre & Marcos Gabarda Inat
 *
 */
void Huffman::creaHuffman () {

  /**
   * Ordenamos la fuente de memoria nula de menor frecuencia a mayor
   * frecuencia.
   */

  int nLongitud = m_vFuente.size();
  
  if (nLongitud == 1) {
    return;
  }

  if (nLongitud > 2) {
    m_vFuente = qsort(m_vFuente);
  }

  Node *NuevoNodo = m_vFuente[0]->merge(m_vFuente[1]);
  
  /**
   * Eliminamos los 2 primeros elementos, que ya hemos fusionado.
   */
  vector<Node *>::iterator it = m_vFuente.begin();
  it = m_vFuente.erase(it);
  m_vFuente.erase(it);
  
  m_vFuente.push_back(NuevoNodo);
  
  if (nLongitud == 2)
    return;
  
  creaHuffman();
}

COD Huffman::generaCodigo() {

  Node Arbol = *m_vFuente[0];

  return Arbol.DTA();

}
