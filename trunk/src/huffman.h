#ifndef _BIN_TREE_
#define _BIN_TREE_

#include "types.h"
#include "node.h"

/**
 * \class Huffman
 *
 * Clase que modela la generación del &aacute;rbol de codificaci&oacute;n 
 * Huffman, a partir de una fuente de memoria nula.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 */
class Huffman {

 private:

  /**
   * \var m_vFuente
   * Vector de sub-&aacute;rboles de codificaci&oacute;n Huffman
   */
  vector<Node *> m_vFuente;

 public:

  Huffman (FMN origen);
  void creaHuffman ();
  COD generaCodigo();
  Node *getTree();

};

#endif
