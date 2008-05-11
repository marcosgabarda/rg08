#ifndef _NODE_
#define _NODE_

class Node {
 private:
  char m_cData;
  bool m_bIsLeaf;
  double m_dProb;
  Node *m_pLeftSon; // Hijo 0
  Node *m_pRightSon; // Hijo 1
 public:

  stack<char> m_CodigoTemporal;
  string m_CodigoHoja;
  COD m_CodigoFinal;

  Node ();
  Node (char cData, double dProb);
  Node *merge(Node *A);
  
  void setProb (double dProb);
  void setLeftSon (Node *pA);
  void setRightSon (Node *pA);
  void setIsLeaf(bool bIsLeaf);
  void setData (char cData);

  double getProb();
  Node *getLeftSon();
  Node *getRightSon();
  bool getIsLeaf();
  char getData();

  COD DTA();
  void _DTA(stack<char> S, Node *root);
  
};

#endif
