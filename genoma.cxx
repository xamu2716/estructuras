#include "genoma.h"
#include <fstream>

static std::string trimBoth(const std::string& s) {
    int n = (int)s.size(), i = 0, j = n - 1;
    while (i <= j && (s[i]==' '||s[i]=='\t'||s[i]=='\r'||s[i]=='\n')) ++i;
    while (j >= i && (s[j]==' '||s[j]=='\t'||s[j]=='\r'||s[j]=='\n')) --j;
    if (i > j) return "";
    return s.substr(i, j - i + 1);
}

void Genoma::clear() { secuencias.clear(); }

bool Genoma::cargarFASTA(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) return false;

    secuencias.clear();
    std::string line;
    Secuencia actual;
    bool leyendo = false;

    while (std::getline(in, line)) {
        if (line.empty()) continue;
        if (line[0] == '>') {
            if (leyendo) {
                secuencias.push_back(actual);
                actual = Secuencia();
            }
            actual.descripcion = trimBoth(line.substr(1));
            actual.bases.clear();
            actual.anchoLinea = 0;
            leyendo = true;
        } else {
            if (actual.anchoLinea == 0) {
                actual.anchoLinea = (int)line.size();
            }
            actual.bases += trimBoth(line);
        }
    }
    if (leyendo) secuencias.push_back(actual);
    return true;
}

bool Genoma::guardarFASTA(const std::string& path) const {
    std::ofstream out(path, std::ios::trunc);
    if (!out.is_open()) return false;

    for (size_t i = 0; i < secuencias.size(); ++i) {
        const Secuencia& s = secuencias[i];
        s.escribirFASTA(out);
    }
    return true;
}

int Genoma::cantidad() const { return (int)secuencias.size(); }

const std::vector<Secuencia>& Genoma::datos() const { return secuencias; }

Secuencia* Genoma::get(const std::string& descripcion) {
    for (size_t i = 0; i < secuencias.size(); ++i) {
        Secuencia& s = secuencias[i];
        if (s.descripcion == descripcion) return &s;
    }
    return 0;
}

int Genoma::contarSubseqGlobal(const std::string& sub) const {
    int total = 0;
    for (size_t i = 0; i < secuencias.size(); ++i) {
        const Secuencia& s = secuencias[i];
        total += s.contarSubsecuencia(sub);
    }
    return total;
}

int Genoma::enmascararGlobal(const std::string& sub) {
    int total = 0;
    for (size_t i = 0; i < secuencias.size(); ++i) {
        Secuencia& s = secuencias[i];
        total += s.enmascararSubsecuencia(sub);
    }
    return total;
}
