#include "utils.h"
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

  return caracterFrecuencia;
}

char creaOcteto (string sCodigo) {

  int nLongitud = sCodigo.size();

  if (nLongitud < 8)  {
    //Extender la cadena
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
}
