#include "fabin.h"
#include <fstream>

// ===== helpers IO =====
void FabinIO::escribirByte(std::ostream& os, unsigned char c) { os.write((const char*)&c, 1); }
bool FabinIO::leerByte(std::istream& is, unsigned char& c) { is.read((char*)&c, 1); return is.good(); }

void FabinIO::escribirU16(std::ostream& os, unsigned short v) {
    unsigned char b0 = (unsigned char)(v & 0xFFu);
    unsigned char b1 = (unsigned char)((v >> 8) & 0xFFu);
    os.write((const char*)&b0, 1); os.write((const char*)&b1, 1);
}
void FabinIO::escribirU32(std::ostream& os, unsigned int v) {
    unsigned char b0 = (unsigned char)(v & 0xFFu);
    unsigned char b1 = (unsigned char)((v >> 8) & 0xFFu);
    unsigned char b2 = (unsigned char)((v >> 16) & 0xFFu);
    unsigned char b3 = (unsigned char)((v >> 24) & 0xFFu);
    os.write((const char*)&b0, 1); os.write((const char*)&b1, 1);
    os.write((const char*)&b2, 1); os.write((const char*)&b3, 1);
}
void FabinIO::escribirU64(std::ostream& os, unsigned long long v) {
    unsigned char b[8];
    int i;
    for (i = 0; i < 8; ++i) b[i] = (unsigned char)((v >> (8*i)) & 0xFFull);
    os.write((const char*)b, 8);
}
bool FabinIO::leerU16(std::istream& is, unsigned short& v) {
    unsigned char b0, b1;
    is.read((char*)&b0, 1); if (!is.good()) return false;
    is.read((char*)&b1, 1); if (!is.good()) return false;
    v = (unsigned short)(b0 | (unsigned short)(b1 << 8));
    return true;
}
bool FabinIO::leerU32(std::istream& is, unsigned int& v) {
    unsigned char b0, b1, b2, b3;
    is.read((char*)&b0, 1); if (!is.good()) return false;
    is.read((char*)&b1, 1); if (!is.good()) return false;
    is.read((char*)&b2, 1); if (!is.good()) return false;
    is.read((char*)&b3, 1); if (!is.good()) return false;
    v = (unsigned int)b0 | ((unsigned int)b1 << 8) | ((unsigned int)b2 << 16) | ((unsigned int)b3 << 24);
    return true;
}
bool FabinIO::leerU64(std::istream& is, unsigned long long& v) {
    unsigned char b[8];
    is.read((char*)b, 8); if (!is.good()) return false;
    v = 0ull;
    int i;
    for (i = 0; i < 8; ++i) v |= ((unsigned long long)b[i]) << (8*i);
    return true;
}

// ===== helpers Huffman =====
static void contarFrecuencias(const Genoma& g, unsigned long long freq[256]) {
    int i, j;
    for (i = 0; i < 256; ++i) freq[i] = 0ull;
    const std::vector<Secuencia>& v = g.datos();
    for (i = 0; i < v.size(); ++i) {
        const std::string& s = v[(size_t)i].bases;
        for (j = 0; j < s.size(); ++j) {
            unsigned char c = (unsigned char)s[(size_t)j];
            freq[c] += 1ull;
        }
    }
}

static void construirParesFrecuencia(const unsigned long long freq[256], std::vector< std::pair<unsigned char, unsigned long long> >& pares, unsigned short& nSimbolos) {
    pares.clear();
    int i;
    for (i = 0; i < 256; ++i) {
        if (freq[i] > 0ull) {
            std::pair<unsigned char, unsigned long long> P;
            P.first = (unsigned char)i;
            P.second = freq[i];
            pares.push_back(P);
        }
    }
    nSimbolos = (unsigned short)pares.size();
}

// agrega los bits de "code" a bytes 
static void agregarBitsDeCodigo(const std::string& code, std::vector<unsigned char>& bytes, unsigned long long& bitCount) {
    int k;
    for (k = 0; k < code.size(); ++k) {
        int bit = (code[(size_t)k] == '1' ? 1 : 0);
        unsigned long long pos = bitCount;
        unsigned long long byteIndex = pos / 8ull;
        int bitIndex = 7 - (pos % 8ull);
        if (byteIndex >= bytes.size()) {
            bytes.push_back((unsigned char)0);
        }
        if (bit) {
            bytes[(size_t)byteIndex] = (unsigned char)(bytes[(size_t)byteIndex] | (unsigned char)(1 << bitIndex));
        }
        bitCount++;
    }
}

// ===== codificar =====
bool FabinIO::codificar(const Genoma& g, const std::string& path) {
    const std::vector<Secuencia>& v = g.datos();
    if (v.empty()) return false;

    unsigned long long freq[256];
    contarFrecuencias(g, freq);

    std::vector< std::pair<unsigned char, unsigned long long> > pares;
    unsigned short nSimbolos = 0;
    construirParesFrecuencia(freq, pares, nSimbolos);
    if (nSimbolos == 0u) return false;

    ArbolHuffman hf;
    if (!hf.construir(pares)) return false;

    std::map<unsigned char, std::string> codes;
    hf.generarCodigos(codes);

    std::ofstream out(path.c_str(), std::ios::binary | std::ios::trunc);
    if (!out.is_open()) return false;

    // encabezado: n, luego n*(c,f) n pares, caracracter y frecuencia
    escribirU16(out, nSimbolos);
    int i, j;
    for (i = 0; i < pares.size(); ++i) {
        escribirByte(out, pares[(size_t)i].first);
        escribirU64(out,  pares[(size_t)i].second);
    }

    // cantidad de secuencias
    unsigned int ns = (unsigned int)v.size();
    escribirU32(out, ns);

    // nombres
    for (i = 0; i < v.size(); ++i) {
        unsigned short li = (unsigned short)v[(size_t)i].descripcion.size();
        escribirU16(out, li);
        const std::string& nom = v[(size_t)i].descripcion;
        for (j = 0; j < nom.size(); ++j) escribirByte(out, (unsigned char)nom[(size_t)j]);
    }

    // por secuencia: wi=cuantas bases tiene, xi=ancho de linea, 
    // bitCount== numero total de bits reales usados para codificar esa secuencia con Huffman 
    for (i = 0; i < v.size(); ++i) {
        const Secuencia& s = v[(size_t)i];
        unsigned long long wi = (unsigned long long)s.bases.size();
        unsigned short xi = (unsigned short)(s.anchoLinea > 0 ? s.anchoLinea : 60);
        escribirU64(out, wi);
        escribirU16(out, xi);

        std::vector<unsigned char> bitstream;
        bitstream.clear();
        unsigned long long bitCount = 0ull;

        for (j = 0; j < s.bases.size(); ++j) {
            unsigned char c = (unsigned char)s.bases[(size_t)j];
            std::map<unsigned char, std::string>::const_iterator it = codes.find(c);
            if (it == std::map<unsigned char, std::string>::const_iterator()) { out.close(); return false; }
            const std::string& code = it->second;
            agregarBitsDeCodigo(code, bitstream, bitCount);
        }

        escribirU64(out, bitCount);
        unsigned long long totalBytes = (bitCount + 7ull) / 8ull;
        unsigned long long b;
        for (b = 0ull; b < totalBytes; ++b) {
            unsigned char by = (b < bitstream.size() ? bitstream[(size_t)b] : (unsigned char)0);
            escribirByte(out, by);
        }
    }

    out.close();
    return true;
}

// ===== decodificar =====
bool FabinIO::decodificar(Genoma& g, const std::string& path) {
    std::ifstream in(path.c_str(), std::ios::binary);
    if (!in.is_open()) return false;

    unsigned short n = 0;
    if (!leerU16(in, n)) { in.close(); return false; }

    std::vector< std::pair<unsigned char, unsigned long long> > pares;
    pares.clear();
    unsigned short k;
    for (k = 0; k < n; ++k) {
        unsigned char c;
        unsigned long long f;
        if (!leerByte(in, c)) { in.close(); return false; }
        if (!leerU64(in, f))  { in.close(); return false; }
        std::pair<unsigned char, unsigned long long> P;
        P.first = c; P.second = f;
        pares.push_back(P);
    }

    unsigned int ns = 0;
    if (!leerU32(in, ns)) { in.close(); return false; }

    std::vector<std::string> nombres;
    nombres.resize(ns);
    unsigned int i;
    for (i = 0; i < ns; ++i) {
        unsigned short li = 0;
        if (!leerU16(in, li)) { in.close(); return false; }
        std::string nom;
        nom.resize(li);
        unsigned short j;
        for (j = 0; j < li; ++j) {
            unsigned char c;
            if (!leerByte(in, c)) { in.close(); return false; }
            nom[(size_t)j] = c;
        }
        nombres[(size_t)i] = nom;
    }

    ArbolHuffman hf;
    if (!hf.construir(pares)) { in.close(); return false; }

    std::vector<Secuencia> rec;
    rec.resize(ns);

    for (i = 0; i < ns; ++i) {
        unsigned long long wi = 0ull;
        unsigned short xi = 0;
        if (!leerU64(in, wi)) { in.close(); return false; }
        if (!leerU16(in, xi)) { in.close(); return false; }

        unsigned long long bitCount = 0ull;
        if (!leerU64(in, bitCount)) { in.close(); return false; }
        unsigned long long totalBytes = (bitCount + 7ull) / 8ull;

        std::vector<unsigned char> bitstream;
        bitstream.resize((size_t)totalBytes);
        unsigned long long b;
        for (b = 0ull; b < totalBytes; ++b) {
            unsigned char c;
            if (!leerByte(in, c)) { in.close(); return false; }
            bitstream[(size_t)b] = c;
        }

        std::string decoded = hf.decodificar(bitstream, bitCount);
        if ((unsigned long long)decoded.size() > wi) decoded = decoded.substr(0, (size_t)wi);

        Secuencia s;
        s.descripcion = nombres[(size_t)i];
        s.bases = decoded;
        s.anchoLinea = xi;
        rec[(size_t)i] = s;
    }

    in.close();

    g.clear();
    for (i = 0; i < ns; ++i) g.secuencias.push_back(rec[(size_t)i]);
    return true;
}
