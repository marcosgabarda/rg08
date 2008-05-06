#include "utils.h"
#include "huffman.h"
#include "types.h"
#include <cmath>

/**
 * Módulo que lee un fichero de texto, y calcula la frecuencia de aparición de 
 * cada símbolo.
 * \author Iván Rodriguez Sastre & Marcos Gabarda Inat
 * \param sFile Dirección absoluta o relativa de la fuente.
 * \return Mapa de caracteres y frecuencia de aparición.
 */
FMN leerFuente(string sFile) {
  FMN caracterFrecuencia;
  ifstream file(sFile.c_str());
  char cCaracter;

  while (file.get(cCaracter)) {
    if (caracterFrecuencia.find(cCaracter) != caracterFrecuencia.end()) {
      caracterFrecuencia[cCaracter]++;
    } else {
      caracterFrecuencia[cCaracter] = 1.;
    }
  }

  FMN::iterator it;
  unsigned int unTam = caracterFrecuencia.size();
  for (it = caracterFrecuencia.begin(); it != caracterFrecuencia.end(); it++) {
    caracterFrecuencia[it->first] = it->second / unTam;
  }

  file.close();
  return caracterFrecuencia;
}

char creaOcteto (string sCodigo, int &nCeros) {

  int nLongitud = sCodigo.size();
  nCeros = 0;
  if (nLongitud < 8)  {
    for (unsigned int i = sCodigo.size(); i < 8; i++ ) {
      sCodigo.push_back('0');
      nCeros++;
    }
  }

  int nSum = 0;
  for (int i = 0; i < nLongitud; i++) {
    char c = sCodigo[i];
    int n = 0;
    if (c == '0') {
      n = 0;
    } else if (c == '1'){
      n = 1;
    }    
    nSum += n*pow(2.0, 7 - i);    
  }
  char cOcteto;
  cOcteto = static_cast<char>(nSum);
  return cOcteto;
}

string recuperaOcteto(char cCodigo, int nCeros) {
  return string("");
}

void serializaArbol(string &sSecuencia, Node *Arbol) {

  if (!Arbol->getIsLeaf()) {
    sSecuencia.push_back('0');
    Node* hijoIzquierdo = Arbol->getLeftSon();
    serializaArbol(sSecuencia, hijoIzquierdo);
    Node* hijoDerecho = Arbol->getRightSon();
    serializaArbol(sSecuencia, hijoDerecho);
  } else {
    sSecuencia.push_back('1');
    char cData = Arbol->getData();
    
    string sBuffer("");
    int iData = static_cast<int>(cData);
    for (int i = iData; i > 1; i/=2) {
      int nResto = i%2;
      if (nResto == 0) {
	sBuffer.push_back('0');
      } else {
	sBuffer.push_back('1');
      }
    }
    sBuffer.push_back('1');
    string sBufferCodigo("");
    for (int i = sBuffer.size() - 1; i >= 0; i--) {
      sBufferCodigo.push_back(sBuffer[i]);
    }

    sSecuencia.append(sBuffer);
   
  }
}


/**
 * Función que escribe en la ruta especificada, el código
 */
void comprimeFichero(string sFile, string sFileOut) {

  FMN frec;
  frec = leerFuente(sFile);  
  Huffman huf(frec);
  huf.creaHuffman();
  COD Codigo = huf.generaCodigo();

  if (sFileOut == "") {
    sFileOut = sFile;
    sFileOut.append(".huf");
  }
  
  ifstream fFuente(sFile.c_str());
  ofstream fSalida(sFileOut.c_str(), ofstream::binary);


  string bufferCodigo("");
  serializaArbol(bufferCodigo, huf.getTree());

  int nCeros;

  char cCaracter;
  while (fFuente.get(cCaracter)) {
    string sCodBinario = Codigo[cCaracter];
    bufferCodigo.append(sCodBinario);    
  }
  fFuente.close();


  string sCodTmp("");    
  for (unsigned int i = 0; i < bufferCodigo.size(); i++) {
    sCodTmp.push_back(bufferCodigo[i]);
    if ((i+1)%8 == 0) { 
      char cCodChar = creaOcteto( sCodTmp,nCeros);
      char buffer[1];
      buffer[0] = cCodChar;
      fSalida.write(buffer, 1);
    }
  }

  if (sCodTmp.size() != 0) {
    char cCodChar = creaOcteto(sCodTmp, nCeros);
    char buffer[1];
    buffer[0] = cCodChar;
    fSalida.write(buffer, 1);
    char cCeros = static_cast<char>(nCeros);
    buffer[0] = cCeros;
    fSalida.write(buffer, 1);
  }
  
  fSalida.close();

}

void descomprimeFichero(string sFile) {
}
