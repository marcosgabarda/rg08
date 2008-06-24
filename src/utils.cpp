#include "utils.h"
#include "huffman.h"
#include "types.h"
#include <cmath>

/**
 * Convierte de un binario, representado por una cadena de caracteres 0 y 1,
 * a un unsigned char, con la codificaci&oacute;n correspondiente en binario
 * real. La secuencia tiene que ser exactamente de 8 caracteres.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] sSecuencia Secuencia binaria a convertir.
 * \return unsigned char
 */
unsigned char bin2char(string sSecuencia) {

  if (sSecuencia.size() != 8) return '\0';

  int nLongitud = static_cast<int>(sSecuencia.size());
  unsigned int nSum = 0;
  for (int i = 0; i < nLongitud; i++) {
    unsigned char c = sSecuencia[i];
    int n = 0;
    if (c == '0') {
      n = 0;
    } else if (c == '1'){
      n = 1;
    }    
    nSum += static_cast<unsigned int>(n*pow(2.0, (nLongitud - 1) - i));
  }
  unsigned char cOcteto;
  cOcteto = static_cast<unsigned char>(nSum);
  return cOcteto;
}

/**
 * Convierte de un unsigned char a un binario, representado por una 
 * cadena de 0s y 1s, con la codificaci&oacute;n correspondiente en binario
 * real.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] cData Caracter a convertir a secuencia binaria.
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
 * M&oacute;dulo que lee un fichero de texto, y calcula la frecuencia de
 * aparici&oacute;n de cada s&iacute;mbolo.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] sFile Direcci&oacute;n absoluta o relativa de la fuente.
 * \return Mapa de caracteres y frecuencia de aparici&oacute;n.
 */
FMN leerFuente(string sFile) {
  FMN caracterFrecuencia;
  ifstream file(sFile.c_str(), ifstream::binary);
  unsigned char cCaracter;
  char buffer[1];

  while (!file.read(buffer, 1).eof()) {
    cCaracter = static_cast<unsigned char>(buffer[0]);
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
 * Funci&oacute;n que crea un unsigned char, a partir de una secuencia de
 * 0s y 1s en una cadena. Adem&aacute;s establece en un par&aacute;metro de
 * salida el numero de ceros de relleno para llegar a 8 bits.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] sCodigo Secuencia de la que obtener el octeto.
 * \param[out] nCeros N&uacute;mero de ceros extras.
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

/**
 * Funci&oacute;n que serializa un &aacute;rbol.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] Arbol Puntero al &aacute;rbol a serializar.
 * \param[out] sSecuencia &Aacute;rbol serializado.
 */
void serializaArbol(string &sSecuencia, Node *Arbol) {

  if (!Arbol->getIsLeaf()) {
    sSecuencia.push_back('0');
    Node* hijoIzquierdo = Arbol->getLeftSon();
    serializaArbol(sSecuencia, hijoIzquierdo);
    Node* hijoDerecho = Arbol->getRightSon();
    serializaArbol(sSecuencia, hijoDerecho);
  } else {
    sSecuencia.push_back('1');
    unsigned char cData = Arbol->getData();
    string sBuffer = char2bin(cData);
    sSecuencia.append(sBuffer);
    cout<< "Codigo: "<<cData<<" Secuencia: "<< sBuffer<<endl;
  }
}

/**
 * Funci&oacute;n que deserializa un &aacute;rbol.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] Arbol Puntero al &aacute;rbol deserializado.
 * \param[out] sSecuencia &Aacute;rbol serializado.
 */
void deserializaArbol(string &sSecuencia, Node *Arbol) {
  unsigned char cBit = sSecuencia[0];
  if (cBit == '1' ) {    
    unsigned char cOcteto = bin2char(sSecuencia.substr(1,8));
    cout<< "Codigo: "<<cOcteto<<" Secuencia: "<< sSecuencia.substr(1,8)<<endl;
    Arbol->setIsLeaf(true);
    Arbol->setData(cOcteto);
    sSecuencia.erase(0,9);
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
 * Funci&oacute;n que escribe en la ruta especificada, el c&oacute;digo 
 * comprimido.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] sFile Nombre del fichero fuente.
 * \param[in] sFileOut Nombre del fichero destino.
 */
void comprimeFichero(string sFile, string sFileOut) {

  cout << "### COMPRIMIENDO ###" << endl;

  /*
   * En primer lugar se crea la fuente de memoria nula leyendo el
   * fichero fuente. Inmediatamente despu&eacute;s se crea el &aacute;rbol
   * de c&oacute;digo Huffman.
   */
  FMN frec;
  frec = leerFuente(sFile);  
  Huffman huf(frec);
  huf.creaHuffman();
  COD Codigo = huf.generaCodigo();

  /*
   * Si no se especifica un nombre de fichero de salida, se a&ntilde;ade la
   * extensi&oacute;n .huf al final.
   */
  if (sFileOut == "") {
    sFileOut = sFile;
    sFileOut.append(".huf");
  }
  
  ifstream fFuente(sFile.c_str());
  ofstream fSalida(sFileOut.c_str(), ofstream::binary);

  /*
   * Obtenemos el &aacute;rbol serializado.
   */
  string bufferCodigo("");
  serializaArbol(bufferCodigo, huf.getTree());

  int nBitsArbol = static_cast<int>(bufferCodigo.size()); 
  fSalida << nBitsArbol;

  cout << "Tamaño del arbol(bits): " << nBitsArbol << endl;
  cout << "Arbol serializado: " << bufferCodigo << endl;

  int nCeros;

  /*
   * Almacenamos el fichero fuente en un buffer y creamos el 
   * c&oacute;digo Huffman.
   */
  char cCaracter;
  unsigned char ucCaracter;
  while (fFuente.get(cCaracter)) {
    ucCaracter = static_cast<unsigned char>(cCaracter);
    string sCodBinario = Codigo[ucCaracter];
    cout << "Cod. Huffman: "<< ucCaracter << " " << sCodBinario << endl;
    bufferCodigo.append(sCodBinario);    
  }
  fFuente.close();

  /*
   * Creamos el fichero destino convirtiendo el buffer de Huffman octeto a
   * octeto.
   */
  string sCodTmp("");    
  for (unsigned int i = 0; i < bufferCodigo.size(); i++) {
    sCodTmp.push_back(bufferCodigo[i]);
    if ((i+1)%8 == 0) { 
      unsigned char cCodChar = creaOcteto( sCodTmp,nCeros);
      char buffer[1];
      buffer[0] = static_cast<char>(cCodChar);
      fSalida.write(buffer, 1);
      sCodTmp = "";
    }
  }
  cout << "Bits fuera de un octeto (nº menor que 8): " << sCodTmp << endl;
  if (sCodTmp.size() != 0) {
    unsigned char cCodChar = creaOcteto(sCodTmp, nCeros);
    char buffer[1];
    buffer[0] = static_cast<char>(cCodChar);
    fSalida.write(buffer, 1);
    unsigned char cCeros = static_cast<unsigned char>(nCeros);
    fSalida << cCeros;
  }
  
  fSalida.close();

}

/**
 * Funci&oacute;n que lee un fichero comprimido.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] sFile Nombre del fichero fuente.
 * \param[out] nLenArbol N&uacute;mero de bits del &aacute;rbol;
 */
string leerComprimido(string sFile, int &nLenArbol) {

  ifstream file(sFile.c_str(), ifstream::binary);
  unsigned char cData;
  char buffer[1];

  string sSecuencia("");

  file >> nLenArbol;

  while (!file.read(buffer, 1).eof()) {
    cData = static_cast<unsigned char>(buffer[0]);
     string sBuffer = char2bin(cData);
     sSecuencia.append(sBuffer);
  }
  file.close();
  return sSecuencia;

}

/**
 * Funci&oacute;n que dada una secuencia de bits y el &aacute;rbol, decodifica
 * dicha secuencia devolviendo el s&iacute;mbolo asociado.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in,out] sSecuencia Secuencia de bits a decodificar.
 * \param[in] Arbol Puntero al &aacute;rbol.
 * \return unsigned char
 */
unsigned char decodifica(string &sSecuencia, Node *Arbol) {
  if (Arbol->getIsLeaf()) {
    cout << " " << Arbol->getData();
    return Arbol->getData();
  } else {
    unsigned char cBit = sSecuencia[0];
    cout << cBit;
    sSecuencia.erase(0,1);
    if (cBit == '1') {
      return decodifica(sSecuencia, Arbol->getRightSon());
    } else if (cBit == '0') {
      return decodifica(sSecuencia, Arbol->getLeftSon());
    }
  }
  return '\0';
}

/**
 * Funci&oacute;n que descomprime un fichero comprimido.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] sFile Nombre del fichero comprimido.
 * \param[in] sFileOut Nombre del fichero de salida.
 */
void descomprimeFichero(string sFile, string sFileOut) {
  int nLenArbol;

  /*
   * En primer lugar leeremos el fichero comprimido.
   */
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

  /*
   * Tras obtener el c&oacute;digo asociado al &aacute;rbol serializado,
   * lo deserializamos y obtenemos el buffer de datos.
   */
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

  /*
   * Una vez le&iacute;dos los datos, decodificamos mediante el &aacute;rbol.
   */
  while (bufferDatos.size() > 1) {
    cout << "Cod. Huff: ";
    unsigned char cData = decodifica(bufferDatos, Arbol);
    cout << endl;
    char buffer[1];
    buffer[0] = static_cast<char>(cData);
    fSalida.write(buffer, 1);
  }

  fSalida.close();
}
