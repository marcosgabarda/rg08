#include "utils.h"

/**
 * Un módulo que reciba como datos de entrada una fuente de memoria nula y 
 * proporcione como salida un código de Huffman binario asociado a la misma.
 * \author Iván Rodriguez Sastre & Marcos Gabarda Inat
 * \param sFile Dirección absoluta o relativa de la fuente.
 * \return Mapa de caracteres y frecuencia de aparición.
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
