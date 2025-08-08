#ifndef COMANDOS_H
#define COMANDOS_H

#include <string>
using namespace std;

// Procesa una linea completa. Retorna true si el programa debe terminar.
bool procesarLinea(const string& linea);

// Comandos (reciben la parte "resto" de la linea)
bool cmdAyuda(const string& resto);
bool cmdCargar(const string& resto);
bool cmdListar(const string& resto);
bool cmdHistograma(const string& resto);
bool cmdEsSubsec(const string& resto);
bool cmdEnmascarar(const string& resto);
bool cmdGuardar(const string& resto);
bool cmdCodificar(const string& resto);
bool cmdDecodificar(const string& resto);
bool cmdRutaMasCorta(const string& resto);
bool cmdBaseRemota(const string& resto);
bool cmdSalir();

#endif
