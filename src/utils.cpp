#include "utils.h"
#include "huffman.h"
#include "types.h"
#include <cmath>

unsigned char bin2char(string sSecuencia) {

  if (sSecuencia.size() != 8) return '\0';

  int nLongitud = static_cast<int>(sSecuencia.size());
  int nSum = 0;
  for (int i = 0; i < nLongitud; i++) {
    char c = sSecuencia[i];
    int n = 0;
    if (c == '0') {
      n = 0;
    } else if (c == '1'){
      n = 1;
    }    
    nSum += n*pow(2.0, (nLongitud - 1) - i);
  }
  unsigned char cOcteto;
  cOcteto = static_cast<unsigned char>(nSum);
  return cOcteto;
}

string char2bin(unsigned char cData) {
  string sBuffer("");
  for (unsigned char i = cData; i > 1; i/=2) {
    unsigned char nResto = i%2;
    if (nResto == 0) {
      sBuffer.push_back('0');
    } else {
      sBuffer.push_back('1');
    }
  }
  sBuffer.push_back('1');
  string sBufferFinal("");
  int nLongitud = static_cast<int>(sBuffer.size());
  for (int i = 0; i < (8 - nLongitud); i++ ) sBufferFinal.push_back('0');
  for(int i = nLongitud; i >= 0; i-- ) sBufferFinal.push_back(sBuffer[i]);
  return sBufferFinal;
}

/**
 * Módulo que lee un fichero de texto, y calcula la frecuencia de aparición de 
 * cada símbolo.
 * \author Iván Rodriguez Sastre & Marcos Gabarda Inat
 * \param sFile Dirección absoluta o relativa de la fuente.
 * \return Mapa de caracteres y frecuencia de aparición.
 */
FMN leerFuente(string sFile) {
  FMN caracterFrecuencia;
  ifstream file(sFile.c_str(), ifstream::binary);
  char cCaracter;
  char buffer[1];

  while (!file.read(buffer, 1).eof()) {
    cCaracter = buffer[0];
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
    cout << "Byte de relleno: " << sCodigo << endl;
  }

  /*  int nSum = 0;
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
  return cOcteto;*/
  return bin2char(sCodigo);
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
    
    /*string sBuffer("");
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
      }*/
    string sBuffer = char2bin(cData);
    sSecuencia.append(sBuffer);
   
  }
}


void deserializaArbol(string &sSecuencia, Node *Arbol) {
  char cBit = sSecuencia[0];
  if (cBit == '1' ) {    
    /*int nSum = 0;
    for (int i = 1; i <= 8; i++) {
      char c = sSecuencia[i];
      int n = 0;
      if (c == '0') {
	n = 0;
      } else if (c == '1'){
	n = 1;
      }    
      nSum += n*pow(2.0, 7 - i);
    }
    char cOcteto;
    cOcteto = static_cast<char>(nSum);    */
    char cOcteto = bin2char(sSecuencia.substr( 1, 7));
    Arbol->setIsLeaf(true);
    Arbol->setData(cOcteto);
    sSecuencia.erase(0, 7);
  } else {
    sSecuencia.erase(0,1);
    Node *nuevoIzquierdo = new Node();
    Arbol->setLeftSon(nuevoIzquierdo);
    deserializaArbol(sSecuencia, nuevoIzquierdo);
    Node *nuevoDerecho = new Node();
    Arbol->setRightSon(nuevoDerecho);
    deserializaArbol(sSecuencia, nuevoDerecho);
  }

}


/**
 * Función que escribe en la ruta especificada, el código
 */
void comprimeFichero(string sFile, string sFileOut) {

  cout << "### COMPRIMIENDO ###" << endl;

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

  int nBitsArbol = bufferCodigo.size(); 
  fSalida << nBitsArbol;

  cout << "Tamaño del arbol(bits): " << nBitsArbol << endl;
  cout << "Arbol serializado: " << bufferCodigo << endl;

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
      sCodTmp = "";
    }
  }
  cout << "Bits fuera de un octeto (nº menor que 8): " << sCodTmp << endl;
  if (sCodTmp.size() != 0) {
    char cCodChar = creaOcteto(sCodTmp, nCeros);
    char buffer[1];
    buffer[0] = cCodChar;
    fSalida.write(buffer, 1);
    /*char cCeros = static_cast<char>(nCeros);
    buffer[0] = cCeros;
    cout << "Numero de ceros extras: " << nCeros << endl;
    fSalida.write(buffer, 1);*/
    fSalida << nCeros;
  }
  
  fSalida.close();

}

string leerComprimido(string sFile, int &nLenArbol) {

  ifstream file(sFile.c_str(), ifstream::binary);
  char cData;
  char buffer[1];

  string sSecuencia("");

  file >> nLenArbol;

  while (!file.read(buffer, 1).eof()) {
     cData = buffer[0];
     /*string sBuffer("");
     //     unsigned int iData = static_cast<unsigned int>(cData);
     for (char i = cData; i > 1; i/=2) {
       char nResto = i%2;
       if (nResto == 0) {
	 sBuffer.push_back('0');
       } else {
	 sBuffer.push_back('1');
       }
     }
     sBuffer.push_back('1');*/
     string sBuffer = char2bin(cData);
     sSecuencia.append(sBuffer);
  }
  file.close();
  return sSecuencia;

}

char decodifica(string &sSecuencia, Node *Arbol) {
  if (Arbol->getIsLeaf()) {
    return Arbol->getData();
  } else {
    string subSecuencia = sSecuencia.substr(1, sSecuencia.size() - 1);
    if (sSecuencia[0] == '1') {
      return decodifica(subSecuencia, Arbol->getRightSon());
    } else if (sSecuencia[0] == '0') {
      return decodifica(subSecuencia, Arbol->getLeftSon());
    }
  }
  return '\0';
}

void descomprimeFichero(string sFile, string sFileOut) {
  int nLenArbol;

  cout << "### DESCOMPRIMIENDO ###" << endl;

  cout << "Leyedo comprimido...";
  string bufferComprimido = leerComprimido(sFile, nLenArbol);
  cout << " OK" << endl;
  cout << "Fichero comprimido (sin el primer entero): " <<  bufferComprimido << endl;
  cout << "Tamaño del buffer: " << bufferComprimido.size() << endl;
  cout << "Arbol de tamaño (bits): " << nLenArbol << endl;

  Node *Arbol = new Node();
  string subSecuencia = bufferComprimido.substr(0, nLenArbol);
  cout << "Arbol serializado: " << subSecuencia << endl;

  cout << "Deserializando arbol...";
  deserializaArbol(subSecuencia, Arbol);
  cout << " OK" << endl;

  string bufferDatosTerm = bufferComprimido.substr(nLenArbol, bufferComprimido.size() - nLenArbol);
  string bufferDatos = bufferDatosTerm.substr(0, bufferDatosTerm.size() - sizeof(int)*8);
  string bufferTerm = bufferDatosTerm.substr(bufferDatosTerm.size() - sizeof(int)*8, sizeof(int)*8);


  int nSum = 0;
  int nLongitud = static_cast<int>(bufferTerm.size());
  cout << "Terminador (secuencia de bits): " << bufferTerm << endl;
  cout << "Tamaño del terminador (nº de bits): " << nLongitud << endl;
  for (int i = 0; i < nLongitud; i++) {
    char c = bufferTerm[i];
    int n = 0;
    if (c == '0') {
      n = 0;
    } else if (c == '1'){
      n = 1;
    }    
    nSum += n*pow(2.0, (nLongitud - 1) - i);    
  }
  cout << "Numero de ceros de relleno: " << nSum << endl;
  

  ofstream fSalida(sFileOut.c_str(), ofstream::binary);

  bufferDatos = bufferDatos.substr(0, bufferDatos.size() - nSum - 1);
  while (bufferDatos.size() != 0) {
    char cData = decodifica(bufferDatos, Arbol);
    fSalida << cData;
  }

  fSalida.close();
}
