#include "utilidades.h"
#include <sstream>

std::string firstToken(const std::string& linea) {
    std::istringstream iss(linea);
    std::string token;
    iss >> token;
    return token;
}

std::string restAfterFirst(const std::string& linea) {
    std::istringstream iss(linea);
    std::string token;
    iss >> token; // descartar la primera palabra
    std::string resto;
    std::getline(iss, resto);
    // eliminar espacios iniciales si los hay
    size_t pos = resto.find_first_not_of(" \t");
    if (pos != std::string::npos) return resto.substr(pos);
    return "";
}
int countWords(const std::string& linea) {
    std::istringstream iss(linea);
    std::string token;
    int cnt = 0;
    while (iss >> token) ++cnt;
    return cnt;
}
