#include "utils.h"

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
