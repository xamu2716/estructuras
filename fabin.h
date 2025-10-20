#ifndef FABIN_H
#define FABIN_H

#include <string>
#include <vector>
#include <map>
#include "genoma.h"
#include "arbol_huffman.h"

class FabinIO {
public:
    static bool codificar(const Genoma& g, const std::string& path);
    static bool decodificar(Genoma& g, const std::string& path);

private:
    // funciones auxiliares
    static void escribirU16(std::ostream& os, unsigned short v);
    static void escribirU32(std::ostream& os, unsigned int v);
    static void escribirU64(std::ostream& os, unsigned long long v);
    static bool leerU16(std::istream& is, unsigned short& v);
    static bool leerU32(std::istream& is, unsigned int& v);
    static bool leerU64(std::istream& is, unsigned long long& v);

    static void escribirByte(std::ostream& os, unsigned char c);
    static bool leerByte(std::istream& is, unsigned char& c);
};

#endif
