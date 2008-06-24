#ifndef _TYPES_
#define _TYPES_

#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

/**
 * \typedef FMN
 *
 * Definici&oacute;n del tipo de datos que modela una fuente de memoria 
 * nula.
 */
typedef map<unsigned char, double> FMN;

/**
 * \typedef COD
 *
 * Mapa para la codificación: 
 * simbolo(char) -> codigo(binario)
 */
typedef map< unsigned char, string> COD;

#endif
