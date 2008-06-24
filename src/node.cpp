#include "types.h"
#include "node.h"

/**
 * Constructor por defecto. Inicializa el nodo como nodo intermedio sin hijos.
 */
Node::Node () {
  m_bIsLeaf = false;
  m_pLeftSon = 0;
  m_pRightSon = 0;
}

/**
 * Constructor sobrecargado. Inicializa el nodo como nodo hoja sin hijos, con
 * el s&iacute;mbolo pasado por par&aacute;metro y la probabilidad asociada.
 *
 * \param[in] cData S&iacute;mbolo a almacenar en la hoja.
 * \param[in] dProb Probabilidad a almacenar en la hoja.
 */
Node::Node (unsigned char cData, double dProb) {
  m_dProb = dProb;
  m_cData = cData;  
  m_bIsLeaf = true;
  m_pLeftSon = 0;
  m_pRightSon = 0;
}

/**
 * Establece la probabilidad del s&iacute;mbolo.
 */
void Node::setProb (double dProb) {
  m_dProb = dProb;
}

/**
 * Obtiene la probabilidad del s&iacute;mbolo.
 */
double Node::getProb() {
  return m_dProb;
}

/**
 * Establece el nodo descendiente izquierdo.
 *
 * \param[in] pA Puntero al nodo descendiente.
 */
void Node::setLeftSon (Node *pA) {
  m_pLeftSon = pA;
}

/**
 * Establece el nodo descendiente derecho.
 *
 * \param[in] pA Puntero al nodo descendiente.
 */
void Node::setRightSon (Node *pA) {
  m_pRightSon = pA;
}

/**
 * Establece si el nodo es hoja o no.
 *
 * \param[in] bIsLeaf Booleano que establece la condici&oacute;n de hoja.
 */
void Node::setIsLeaf(bool bIsLeaf){
  m_bIsLeaf = bIsLeaf;
}

/**
 * Obtiene el nodo descendiente izquierdo.
 */
Node *Node::getLeftSon(){
  return m_pLeftSon;
}

/**
 * Obtiene el nodo descendiente derecho.
 */
Node *Node::getRightSon(){
  return m_pRightSon;
}

/**
 * Obtiene si un nodo es hoja o no.
 */
bool Node::getIsLeaf(){
  return m_bIsLeaf;
}

/**
 * Obtiene el s&iacute;mbolo asociado al nodo hoja.
 */
unsigned char Node::getData(){
  return m_cData;
}

/**
 * M&eacute;todo que fusiona dos nodos creando un nodo intermedio que los acoge.
 */
Node* Node::merge (Node *A) {
  Node *Union = new Node();
  Union->setProb(this->m_dProb + A->getProb());
  Union->setLeftSon(this);
  Union->setRightSon(A);

  return Union;
}

/**
 * M&eacute;todo que encapsula llamadas a _DTA para poder realizar el recorrido
 * en profundidad del &aacute;rbol.
 */
COD Node::DTA(){
  if (!m_bIsLeaf) {

    if (m_pLeftSon) {
      //cout << "[Raiz]Bajamos por la rama izquierda." << endl;
      m_CodigoTemporal.push('0');
      m_pLeftSon->_DTA(m_CodigoTemporal, this);
      m_CodigoTemporal.pop();
    }
    if (m_pRightSon) {
      m_CodigoTemporal.push('1');
      m_pRightSon->_DTA(m_CodigoTemporal, this);
      m_CodigoTemporal.pop();
    }
  } 
  return m_CodigoFinal;
}

/**
 * M&eacute;todo que recorre el &aacute;rbol en profundidad.
 */
void Node::_DTA(stack<unsigned char> S, Node *root) {
  if (!m_bIsLeaf) {
    if (m_pLeftSon) {
      S.push('0');
      m_pLeftSon->_DTA(S, root);
      S.pop();
    }
    if (m_pRightSon) {
      S.push('1');      
      m_pRightSon->_DTA(S, root );
      S.pop();
    }
  } else {    
    while (!S.empty()) {
      unsigned char c = S.top();
      S.pop();
      m_CodigoHoja.push_back(c);
    }
    root->m_CodigoFinal[m_cData] = m_CodigoHoja;
  }
}

/**
 * Establece el s&iacute;mbolo del nodo hoja.
 *
 * \param[in] cData Caracter correspondiente al s&iacute;mbolo a almacenar.
 */
void Node::setData (unsigned char cData) {
  m_cData = cData;
}
