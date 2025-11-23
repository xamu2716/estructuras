#ifndef COMANDOS_H
#define COMANDOS_H

#include <string>
class Sistema;

bool procesarLinea(const std::string& linea, Sistema& sistema);

bool cmdAyuda(const std::string& resto);
bool cmdCargar(const std::string& resto, Sistema& sistema);
bool cmdListar(const std::string& resto, Sistema& sistema);
bool cmdHistograma(const std::string& resto, Sistema& sistema);
bool cmdEsSubsec(const std::string& resto, Sistema& sistema);
bool cmdEnmascarar(const std::string& resto, Sistema& sistema);
bool cmdGuardar(const std::string& resto, Sistema& sistema);
bool cmdCodificar(const std::string& resto, Sistema& sistema);
bool cmdDecodificar(const std::string& resto, Sistema& sistema);
bool cmdRutaMasCorta(const std::string& resto, Sistema& sistema);
bool cmdBaseRemota(const std::string& resto, Sistema& sistema);

bool cmdSalir();

#endif
