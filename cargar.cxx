#include "cargar.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string cargarSecuencias(const std::string& nombreArchivo,
                             std::vector<Secuencia>& secuencias) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        return nombreArchivo + " no se encuentra o no puede leerse.";
    }

    // Sobrescribir cualquier secuencia previa
    secuencias.clear();

    std::string linea;
    Secuencia actual;
    bool leyendoSecuencia = false;

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        if (linea[0] == '>') {
            // Guardar la secuencia anterior si existía
            if (leyendoSecuencia) {
                secuencias.push_back(actual);
                actual = Secuencia();
            }
            actual.descripcion = linea.substr(1); // quitar el '>'
            actual.bases.clear();
            leyendoSecuencia = true;
        } else {
            // Agregar las bases (concatenar las líneas)
            actual.bases += linea;
        }
    }

    // Guardar la última secuencia si existe
    if (leyendoSecuencia) {
        secuencias.push_back(actual);
    }

    if (secuencias.empty()) {
        return nombreArchivo + " no contiene ninguna secuencia.";
    } else if (secuencias.size() == 1) {
        return "1 secuencia cargada correctamente desde " + nombreArchivo + ".";
    } else {
        return std::to_string(secuencias.size()) +
               " secuencias cargadas correctamente desde " + nombreArchivo + ".";
    }
}
