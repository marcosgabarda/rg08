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

typedef map<unsigned char, double> FMN;
typedef vector<pair<unsigned char, double> > FMNO;

/**
 * Mapa para la codificación: 
 * simbolo(char) -> codigo(binario)
 */
typedef map< unsigned char, string> COD;

#endif
