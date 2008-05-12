#include "utils.h"

/**
 * Un m�dulo que reciba como datos de entrada una fuente de memoria nula y 
 * proporcione como salida un c�digo de Huffman binario asociado a la misma.
 * \author Iv�n Rodriguez Sastre & Marcos Gabarda Inat
 * \param sFile Direcci�n absoluta o relativa de la fuente.
 * \return Mapa de caracteres y frecuencia de aparici�n.
 */

int main(int argc, char* argv[]) {

  if (argc == 1) {
    cerr << "Uso: " << argv[0] << " origen [destino]" << endl;
  }

  if (argc == 2) {
    string sFile(argv[1]);
    comprimeFichero(sFile);
  } else if (argc == 3) {
    string sFile(argv[1]);
    string sFileOut(argv[2]);
    comprimeFichero(sFile, sFileOut);
  }
  
  return 0;
}
