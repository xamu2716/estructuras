#ifndef COMANDOS_H
#define COMANDOS_H

#include <string>
class Genoma;

bool procesarLinea(const std::string& linea, Genoma& genoma);

bool cmdAyuda(const std::string& resto);
bool cmdCargar(const std::string& resto, Genoma& genoma);
bool cmdListar(const std::string& resto, Genoma& genoma);
bool cmdHistograma(const std::string& resto, Genoma& genoma);
bool cmdEsSubsec(const std::string& resto, Genoma& genoma);
bool cmdEnmascarar(const std::string& resto, Genoma& genoma);
bool cmdGuardar(const std::string& resto, Genoma& genoma);

bool cmdSalir();

#endif
