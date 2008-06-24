#include "types.h"
#include "huffman.h"
#include "qsort.h"

/**
 * Constructor de la clase Huffman. Tiene como par&aacute;metro una fuente de
 * memoria nula.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] Origen Fuente de memoria nula.
 */
Huffman::Huffman (FMN Origen) {
  
  vector<Node *> vFuente(Origen.size());
  int i = 0;

  /**
   * Genera un &aacute;rbol por cada s&iacute;mbolo de la fuente de memoria nula.
   */
  for (  FMN::iterator it = Origen.begin(); it != Origen.end(); it++, i++) {
    Node *Leaf = new Node(it->first, it->second);
    vFuente[i] = Leaf;
  }
  m_vFuente = vFuente;
  
}

/**
 * M&eacute;todo que contruye el arbol de forma recursiva. Dentro de un vector de 
 * &aacute;rboles, seleccionamos los dos con una menor frecuencia, y los fusionamos, 
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
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 *
 */
void Huffman::creaHuffman () {

  /**
   * En primer lugar, ordenamos la fuente de memoria nula de menor 
   * frecuencia a mayor frecuencia. Para esta ordenaci&oacute;n usamos
   * una implementaci&oacute;n propia del algoritmo de QuickSort para el
   * caso de ordenar vecotres de &aacute;rboles de codificaci&oacute;n
   * Huffman.
   */

  int nLongitud = m_vFuente.size();
  
  if (nLongitud == 1) {
    return;
  }

  if (nLongitud > 2) {
    m_vFuente = qsort(m_vFuente);
  }

  /**
   * Seleccionamos los dos &aacute;rboles con mayor frecuencia, y los
   * fusionamos.
   */
  Node *NuevoNodo = m_vFuente[0]->merge(m_vFuente[1]);
  
  /**
   * Luego eliminamos los 2 primeros elementos, que ya hemos fusionado.
   */
  vector<Node *>::iterator it = m_vFuente.begin();
  it = m_vFuente.erase(it);
  m_vFuente.erase(it);
  
  m_vFuente.push_back(NuevoNodo);
  
  /**
   * El algoritmo se ejecuta recursivamente hasta que s&oacute;lo queden un 
   * &aacute;rbol.
   */
  if (nLongitud == 2)
    return;
  
  creaHuffman();
}

/**
 * M&eacute;todo que devuelve el c&oacute;digo Huffman generado por la clase.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \return COD C&oacute;digo generado.
 */
COD Huffman::generaCodigo() {

  Node Arbol = *m_vFuente[0];

  return Arbol.DTA();

}

/**
 * M&eacute;todo que devuelve el nodo ra&iacute;z del &aacute;rbol Huffman.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \return Node* Puntero al nodo ra&iacute;z.
 */
Node* Huffman::getTree() {
  return m_vFuente[0];
}
