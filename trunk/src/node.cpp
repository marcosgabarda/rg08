#include "types.h"
#include "node.h"


Node::Node () {
  m_bIsLeaf = false;
  m_pLeftSon = 0;
  m_pRightSon = 0;
}

Node::Node (unsigned char cData, double dProb) {
  m_dProb = dProb;
  m_cData = cData;  
  m_bIsLeaf = true;
  m_pLeftSon = 0;
  m_pRightSon = 0;
}

void Node::setProb (double dProb) {
  m_dProb = dProb;
}

double Node::getProb() {
  return m_dProb;
}

void Node::setLeftSon (Node *pA) {
  m_pLeftSon = pA;
}

void Node::setRightSon (Node *pA) {
  m_pRightSon = pA;
}

void Node::setIsLeaf(bool bIsLeaf){
  m_bIsLeaf = bIsLeaf;
}

Node *Node::getLeftSon(){
  return m_pLeftSon;
}

Node *Node::getRightSon(){
  return m_pRightSon;
}

bool Node::getIsLeaf(){
  return m_bIsLeaf;
}

unsigned char Node::getData(){
  return m_cData;
}

Node* Node::merge (Node *A) {
  Node *Union = new Node();
  Union->setProb(this->m_dProb + A->getProb());
  Union->setLeftSon(this);
  Union->setRightSon(A);

  return Union;
}

COD Node::DTA(){
  if (!m_bIsLeaf) {

    if (m_pLeftSon) {
      //cout << "[Raiz]Bajamos por la rama izquierda." << endl;
      m_CodigoTemporal.push('0');
      m_pLeftSon->_DTA(m_CodigoTemporal, this);
      m_CodigoTemporal.pop();
    }
    if (m_pRightSon) {
      //cout << "[Raiz]Bajamos por la rama derecha." << endl;
      m_CodigoTemporal.push('1');
      m_pRightSon->_DTA(m_CodigoTemporal, this);
      m_CodigoTemporal.pop();
    }
  } 
  return m_CodigoFinal;
}

void Node::_DTA(stack<unsigned char> S, Node *root) {
  if (!m_bIsLeaf) {
    if (m_pLeftSon) {
      //cout << "Bajamos por la rama izquierda." << endl;
      S.push('0');
      m_pLeftSon->_DTA(S, root);
      S.pop();
    }
    if (m_pRightSon) {
      //cout << "Bajamos por la rama derecha." << endl;
      S.push('1');      
      m_pRightSon->_DTA(S, root );
      S.pop();
    }
  } else {    
    //cout << "Llegamos a la hoja: " << m_cData << endl;
    while (!S.empty()) {
      unsigned char c = S.top();
      S.pop();
      m_CodigoHoja.push_back(c);
    }
    //string cadena;
    //cadena.push_back(m_cData);
    root->m_CodigoFinal[m_cData] = m_CodigoHoja;
  }
}

void Node::setData (unsigned char cData) {
  m_cData = cData;
}
