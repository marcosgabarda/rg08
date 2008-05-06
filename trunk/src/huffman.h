#ifndef _BIN_TREE_
#define _BIN_TREE_

#include "types.h"
#include "node.h"

class Huffman {
 private:
  vector<Node *> m_vFuente;
 public:
  Huffman (FMN origen);
  void creaHuffman ();
  COD generaCodigo();
  Node *getTree();
};

#endif
