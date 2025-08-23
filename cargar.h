#ifndef CARGAR_H
#define CARGAR_H

#include <string>
#include <vector>
#include "secuencia.h"

// Carga las secuencias desde un archivo FASTA y devuelve el mensaje correspondiente
std::string cargarSecuencias(const std::string& nombreArchivo,
                             std::vector<Secuencia>& secuencias);

#endif // CARGAR_H
