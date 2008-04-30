#include "types.h"
#include "huffman.h"
#include "utils.h"

/**
 * Un módulo que reciba como datos de entrada una fuente de memoria nula y 
 * proporcione como salida un código de Huffman binario asociado a la misma.
 * \author Iván Rodriguez Sastre & Marcos Gabarda Inat
 * \param sFile Dirección absoluta o relativa de la fuente.
 * \return Mapa de caracteres y frecuencia de aparición.
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
