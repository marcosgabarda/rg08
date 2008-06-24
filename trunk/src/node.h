#ifndef _NODE_
#define _NODE_

/**
 * \class Node
 *
 * Clase que implementa la representaci&oacute;n de un Nodo del &aacute;rbol
 * de codificaci&oacute;n Huffman.
 *
 * Se usan m&eacute;todos para establecer y recuperar la informaci&oacute;n 
 * de los distintos atributos del nodo.
 *
 * \date Julio 2008
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 *
 */

class Node {
 private:

  /**
   * \var m_cData 
   * Caracter que guarda el s&iacute;mbolo almacenado en el nodo.
   */
  unsigned char m_cData;

  /**
   * \var m_bIsLeaf 
   * Booleano que define si un nodo es hoja o un nodo intermedio.
   */
  bool m_bIsLeaf;

  /**
   * \var m_dProb
   * Double que establece la probabilidad del s&iacute;mbolo.
   */
  double m_dProb;

  /**
   * \var m_pLeftSon
   * Puntero al nodo descendiente por la rama izquierda (Hijo 0).
   */
  Node *m_pLeftSon;

  /**
   * \var m_pRightSon
   * Puntero al nodo descendiente por la rama derecha (Hijo 1).
   */
  Node *m_pRightSon;
 public:

  /**
   * \var m_CodigoTemporal
   * Pila que almacena el c&oacute;digo temporal obtenido al recorrer el
   * &aacutebol;.
   */
  stack<unsigned char> m_CodigoTemporal;

  /**
   * \var m_CodigoHoja
   * Cadena que almacena el c&oacute;digo obtenido al llegar a una hoja.
   */
  string m_CodigoHoja;

  /**
   * \var m_CodigoFinal
   * Cadena que almacena el c&oacute;digo obtenido final tras recorrer el
   * &aacute;rbol.
   */
  COD m_CodigoFinal;

  Node ();
  Node (unsigned char cData, double dProb);
  Node *merge(Node *A);
  
  void setProb (double dProb);
  void setLeftSon (Node *pA);
  void setRightSon (Node *pA);
  void setIsLeaf(bool bIsLeaf);
  void setData (unsigned char cData);

  double getProb();
  Node *getLeftSon();
  Node *getRightSon();
  bool getIsLeaf();
  unsigned char getData();

  COD DTA();
  void _DTA(stack<unsigned char> S, Node *root);
  
};

#endif
