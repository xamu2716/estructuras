#ifndef COMANDOS_H
#define COMANDOS_H

#include <string>
class Genoma;
class Sistema;

bool procesarLinea(const std::string& linea, Sistema& sistema);// true si debe salir

bool cmdAyuda(const std::string& resto);// muestra ayuda
bool cmdCargar(const std::string& resto, Sistema& sistema);// carga un archivo FASTA
bool cmdListar(const std::string& resto, Sistema& sistema);// lista secuencias
bool cmdHistograma(const std::string& resto, Sistema& sistema);// histograma de una secuencia
bool cmdEsSubsec(const std::string& resto, Sistema& sistema);// cuenta subsecuencia en una secuencia
bool cmdEnmascarar(const std::string& resto, Sistema& sistema);// enmascara subsecuencia en una secuencia
bool cmdGuardar(const std::string& resto, Sistema& sistema);// guarda en un archivo FASTA
bool cmdCodificar(const std::string& resto, Sistema& sistema);// codifica en un archivo fabin
bool cmdDecodificar(const std::string& resto, Sistema& sistema);// decodifica desde un archivo fabin

bool cmdSalir();// sale del programa

#endif
