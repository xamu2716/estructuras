#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
using namespace std;

// trim espacios al inicio y final de una cadena
string trim(const string& s);

// Devuelve el primer token (hasta el primer espacio)
string firstToken(const string& s);

// Devuelve lo que queda despues del primer espacio (o "")
string restAfterFirst(const string& s);

// Cuenta palabras separadas por espacios (compacta multiples espacios)
int countWords(const string& s);

// true si s comienza con prefijo (exacto)
bool startsWith(const string& s, const string& prefijo);

// true si s termina con sufijo (exacto)
bool endsWith(const string& s, const string& sufijo);

// true si todos los chars son digitos y no esta vacio
bool esNumero(const string& s);

#endif
