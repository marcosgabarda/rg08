#ifndef _UTILS_
#define _UTILS_

#include "types.h"
#include "node.h"

FMN leerFuente(string sFile);
char creaOcteto (string sCodigo, int &nCeros);
void comprimeFichero(string sFile, string sFileOut = "");
void serializaArbol(string &sSecuencia, Node *Arbol);
void deserializaArbol(string &sSecuencia, Node *Arbol);
string leerComprimido(string sFile, int &nLenArbol);
char decodifica(string &sSecuencia, Node *Arbol);
void descomprimeFichero(string sFile, string sFileOut = "");
unsigned char bin2char(string sSecuencia);
string char2bin(unsigned char cData);

#endif
