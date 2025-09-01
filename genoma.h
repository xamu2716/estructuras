#ifndef GENOMA_H
#define GENOMA_H

#include <string>
#include <vector>
#include "secuencia.h"

class Genoma {
public:
    std::vector<Secuencia> secuencias;

    void clear();
    bool cargarFASTA(const std::string& path);
    bool guardarFASTA(const std::string& path) const;

    int cantidad() const;
    const std::vector<Secuencia>& datos() const;

    Secuencia* get(const std::string& descripcion);

    int contarSubseqGlobal(const std::string& sub) const;
    int enmascararGlobal(const std::string& sub);
};

#endif
