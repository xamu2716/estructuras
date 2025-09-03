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
    void clear(); // vacia el genoma
    bool cargarFASTA(const std::string& path);// carga en el genoma
    bool guardarFASTA(const std::string& path) const;// guarda el genoma

    int cantidad() const;// cantidad de secuencias en el genoma
    const std::vector<Secuencia>& datos() const;// acceso a las secuencias del genoma

    Secuencia* get(const std::string& descripcion);// acceso a una secuencia del genoma

    int contarSubseqGlobal(const std::string& sub) const;// cuenta en todo el genoma
    int enmascararGlobal(const std::string& sub);// enmascara en todo el genoma
};

#endif // SISTEMA_H
