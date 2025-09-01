#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>

// Devuelve la primera palabra de una linea
std::string firstToken(const std::string& linea);

// Devuelve la linea sin la primera palabra
std::string restAfterFirst(const std::string& linea);

// Cuenta cuantas palabras hay en una linea
int countWords(const std::string& linea);

#endif
