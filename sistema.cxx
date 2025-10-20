#include "sistema.h"
#include "fabin.h"

Genoma& Sistema::getGenoma() { return genoma_; }

void Sistema::clear() {
    genoma_.clear();
}

bool Sistema::cargarFASTA(const std::string& path) {
    return genoma_.cargarFASTA(path);
}

bool Sistema::guardarFASTA(const std::string& path) const {
    return genoma_.guardarFASTA(path);
}

bool Sistema::codificarFabin(const std::string& path) const {
    return FabinIO::codificar(genoma_, path);
}

bool Sistema::decodificarFabin(const std::string& path) {
    return FabinIO::decodificar(genoma_, path);
}

int Sistema::cantidad() const {
    return genoma_.cantidad();
}

const std::vector<Secuencia>& Sistema::datos() const {
    return genoma_.datos();
}

Secuencia* Sistema::get(const std::string& descripcion) {
    return genoma_.get(descripcion);
}

int Sistema::contarSubseqGlobal(const std::string& sub) const {
    return genoma_.contarSubseqGlobal(sub);
}

int Sistema::enmascararGlobal(const std::string& sub) {
    return genoma_.enmascararGlobal(sub);
}
