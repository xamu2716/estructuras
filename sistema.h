#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include <vector>
#include "genoma.h"
#include "secuencia.h"

// TAD Sistema: contiene un Genoma y reexpone sus operaciones.

class Sistema {
private:
    Genoma genoma_;

public:

    Genoma& getGenoma();
    void clear();
    bool cargarFASTA(const std::string& path);
    bool guardarFASTA(const std::string& path) const;

    int cantidad() const;
    const std::vector<Secuencia>& datos() const;

    Secuencia* get(const std::string& descripcion);

    int contarSubseqGlobal(const std::string& sub) const;
    int enmascararGlobal(const std::string& sub);
};

#endif // SISTEMA_H
