#include "types.h"
#include "huffman.h"

/**
 * Hola
 * M�dulo que lee un fichero de texto, y calcula la frecuencia de aparici�n de 
 * cada s�mbolo.
 * \author Iv�n Rodriguez Sastre & Marcos Gabarda Inat
 * \param sFile Direcci�n absoluta o relativa de la fuente.
 * \return Mapa de caracteres y frecuencia de aparici�n.
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

  return caracterFrecuencia;
}

/**
 * Un m�dulo que reciba como datos de entrada una fuente de memoria nula y 
 * proporcione como salida un c�digo de Huffman binario asociado a la misma.
 * \author Iv�n Rodriguez Sastre & Marcos Gabarda Inat
 * \param sFile Direcci�n absoluta o relativa de la fuente.
 * \return Mapa de caracteres y frecuencia de aparici�n.
 */

int main(int argc, char* argv[]) {
  string sFile(argv[1]);
  FMN frec;
  frec = leerFuente(sFile);
  
  Huffman huf(frec);
  huf.creaHuffman();
  COD Codigo = huf.generaCodigo();

  cout << "Simbolo\t  \tCodigo" << endl;
  for (COD::iterator it = Codigo.begin(); it != Codigo.end(); it++) {
    cout << it->first << "\t=>\t" << it->second << endl;
  }

  return 0;
}
