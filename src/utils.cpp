#include "utils.h"
#include "huffman.h"
#include "types.h"
#include <cmath>

/**
 * Convierte de un binario, repersentado por una cadena de caracteres 0 y 1, a un 
 * unsigned char, con la codificacion correspondiente en binario real. La secuencia
 * tiene que ser exactamente de 8 caracteres.
 * \author Iván Rodriguez Sastre & Marcos Gabarda Inat
 * \param sSecuencia string
 * \return unsigned char
 */
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

/**
 * Convierte de un unsigned char a un binario, representado por una 
 * cadena de 0's y 1's, con la codificacion correspondiente en binario real.
 * \author Iván Rodriguez Sastre & Marcos Gabarda Inat
 * \param cData unsigned char
 * \return string
 */
string char2bin(unsigned char cData) {
  string sBuffer;
  for (unsigned char i = cData; i > 1; i/=2) {
    unsigned char nResto = i%2;
    if (nResto == 0) {
      sBuffer.push_back('0');
    } else {
      sBuffer.push_back('1');
    }
  }
  sBuffer.push_back('1');
  string sBufferFinal;
  int nLongitud = static_cast<int>(sBuffer.size());
  for (int i = 0; i < (8 - nLongitud); i++ ) sBufferFinal.push_back('0');
  for(int i = nLongitud - 1; i >= 0; i-- ) sBufferFinal.push_back(sBuffer[i]);
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


/**
 * Funcion que crea un unsigned char, a partir de una secuencia de 0's y 1's en
 * una cadena. Ademas establece en un parametro de salida el numero de ceros de
 * relleno para llegar a 8 bits.
 * \author Iván Rodriguez Sastre & Marcos Gabarda Inat
 * \param sCodigo string, nCeros int (salida)
 * \return unsigned char
 */
unsigned char creaOcteto (string sCodigo, int &nCeros) {

  int nLongitud = sCodigo.size();
  nCeros = 0;
  if (nLongitud < 8)  {
    for (unsigned int i = sCodigo.size(); i < 8; i++ ) {
      sCodigo.push_back('0');
      nCeros++;
    }
    cout << "Byte de relleno: " << sCodigo << endl;
  }
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
    string sBuffer = char2bin(cData);
    sSecuencia.append(sBuffer);
   
  }
}


void deserializaArbol(string &sSecuencia, Node *Arbol) {
  char cBit = sSecuencia[0];
  if (cBit == '1' ) {    
    char cOcteto = bin2char(sSecuencia.substr( 1, 8));
    Arbol->setIsLeaf(true);
    Arbol->setData(cOcteto);
    sSecuencia.erase(0, 9);
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

  int nBitsArbol = static_cast<int>(bufferCodigo.size()); 
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
    unsigned char cCeros = static_cast<unsigned char>(nCeros);
    fSalida << cCeros;
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
    char cBit = sSecuencia[0];
    sSecuencia.erase(0,1);
    if (cBit == '1') {
      return decodifica(sSecuencia, Arbol->getRightSon());
    } else if (cBit == '0') {
      return decodifica(sSecuencia, Arbol->getLeftSon());
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
  string bufferDatos = bufferDatosTerm.substr(0, bufferDatosTerm.size() - 8);
  string bufferTerm = bufferDatosTerm.substr(bufferDatosTerm.size() - 8, 8);


  int nLongitud = static_cast<int>(bufferTerm.size());
  cout << "Terminador (secuencia de bits): " << bufferTerm << endl;
  cout << "Tamaño del terminador (nº de bits): " << nLongitud << endl;

  unsigned int nCeros = static_cast<unsigned int>(bin2char(bufferTerm));

  cout << "Numero de ceros de relleno: " << nCeros << endl;
  

  ofstream fSalida(sFileOut.c_str(), ofstream::binary);

  cout << bufferDatos << endl;
  bufferDatos = bufferDatos.substr(0, bufferDatos.size() - nCeros);
  cout << bufferDatos << endl;

  while (bufferDatos.size() > 1) {
    char cData = decodifica(bufferDatos, Arbol);
    char buffer[1];
    buffer[0] = cData;
    fSalida.write(buffer, 1);
  }

  fSalida.close();
}
