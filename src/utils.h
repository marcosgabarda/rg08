#ifndef _UTILS_
#define _UTILS_

#include "types.h"
#include "node.h"

FMN leerFuente(string sFile);
char creaOcteto (string sCodigo, int &nCeros);
string recuperaOcteto(char cCodigo, int nCeros);
void comprimeFichero(string sFile, string sFileOut = "");
void descomprimeFichero(string sFile);
void serializaArbol(string &sSecuencia, Node *Arbol);

#endif
