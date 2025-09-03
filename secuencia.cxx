#include "secuencia.h"
#include <vector>

/*
 * ================================
 *  Funciones internas de Secuencia
 *  (helpers privados de este .cxx)
 * ================================
 */

// Indices para el histograma (orden: A C G T U R Y K M S W B D H V N X -)
static int codeIndex(char c) {
    switch (c) {
        case 'A': return 0; case 'C': return 1; case 'G': return 2; case 'T': return 3;
        case 'U': return 4; case 'R': return 5; case 'Y': return 6; case 'K': return 7;
        case 'M': return 8; case 'S': return 9; case 'W': return 10; case 'B': return 11;
        case 'D': return 12; case 'H': return 13; case 'V': return 14; case 'N': return 15;
        case 'X': return 16; case '-': return 17;
        default:  return -1;
    }
}

// mascaraBase: convierte una letra a una mascara de bits de posibilidades.
// Bits: 0:A 1:C 2:G 3:T 4:U 5:gap('-'). 6 para X
// T y U comparten compatibilidad (bits 3 y 4 activos para ambos).
static unsigned int mascaraBase(char c) {
    switch (c) {
        case 'A': return 1u << 0;
        case 'C': return 1u << 1;
        case 'G': return 1u << 2;
        case 'T': return (1u << 3) | (1u << 4);
        case 'U': return (1u << 3) | (1u << 4);
        case '-': return 1u << 5;
        case 'X': return 1u << 6;

        case 'R': return (1u << 0) | (1u << 2);                                   // A or G
        case 'Y': return (1u << 1) | (1u << 3) | (1u << 4);                       // C or T or U
        case 'K': return (1u << 2) | (1u << 3) | (1u << 4);                       // G or T or U
        case 'M': return (1u << 0) | (1u << 1);                                   // A or C
        case 'S': return (1u << 1) | (1u << 2);                                   // C or G
        case 'W': return (1u << 0) | (1u << 3) | (1u << 4);                       // A or T or U
        case 'B': return (1u << 1) | (1u << 2) | (1u << 3) | (1u << 4);           // C or G or T or U
        case 'D': return (1u << 0) | (1u << 2) | (1u << 3) | (1u << 4);           // A or G or T or U
        case 'H': return (1u << 0) | (1u << 1) | (1u << 3) | (1u << 4);           // A or C or T or U
        case 'V': return (1u << 0) | (1u << 1) | (1u << 2);                       // A or C or G
        case 'N': return (1u << 0) | (1u << 1) | (1u << 2) | (1u << 3) | (1u << 4);// cualquiera

        default:  return 0u; // caracter desconocido: no matchea
    }
}

// equivalenciaMascaras: devuelve true si dos caracteres comparten al menos una base.
static bool equivalenciaMascaras(char seqChar, char patChar) {
    if (seqChar == 'X') return patChar == 'X';
    if (patChar == 'X') return seqChar == 'X';
    
    unsigned int ms = mascaraBase(seqChar);
    unsigned int mp = mascaraBase(patChar);

    unsigned int gapBit = 1u << 5;
    bool seqGap = (ms & gapBit) != 0u;
    bool patGap = (mp & gapBit) != 0u;
    if (seqGap || patGap) return seqGap && patGap;

    return (ms & mp) != 0u;
}

/*
 * ================================
 *  Metodos de la clase Secuencia
 * ================================
 */

Secuencia::Secuencia() : anchoLinea(0) {}

bool Secuencia::esCompleta() const {
    for (char c : bases) if (c == '-') return false;
    return true;
}

int Secuencia::contarBasesValidas() const {
    int cnt = 0;
    for (char c : bases) {
        if (c != '-') ++cnt;
    }
    return cnt;
}

int Secuencia::histograma(int outFreq[18]) const {
    for (int i = 0; i < 18; ++i) outFreq[i] = 0;
    int total = 0;
    for (unsigned char c : bases) {
        int idx = codeIndex((char)c);
        if (idx >= 0) { outFreq[idx]++; total++; }
    }
    return total;
}

// Conteo de apariciones con equivalencias IUPAC (solapamientos permitidos).
int Secuencia::contarSubsecuencia(const std::string& sub) const {
    if (sub.empty()) return 0;
    int n = (int)bases.size();
    int m = (int)sub.size();
    if (m > n) return 0;

    int cnt = 0;
    for (int i = 0; i + m <= n; ++i) {
        bool ok = true;
        for (int j = 0; j < m; ++j) {
            char cs = bases[i + j];
            char cp = sub[j];
            if (!equivalenciaMascaras(cs, cp)) { ok = false; break; }
        }
        if (ok) ++cnt;
    }
    return cnt;
}

// Enmascara con 'X' cada match del patron (equivalencias IUPAC, solapamientos permitidos).
int Secuencia::enmascararSubsecuencia(const std::string& sub) {
    if (sub.empty()) return 0;
    int n = (int)bases.size();
    int m = (int)sub.size();
    if (m > n) return 0;

    // PRIMERO: encontrar todas las posiciones sin modificar
    std::vector<int> startPositions;
    for (int i = 0; i + m <= n; ++i) {
        bool ok = true;
        for (int j = 0; j < m; ++j) {
            char cs = bases[i + j];
            char cp = sub[j];
            if (!equivalenciaMascaras(cs, cp)) {
                ok = false;
                break;
            }
        }
        if (ok) {
            startPositions.push_back(i);
        }
    }
    //enmascarar todas las posiciones encontradas
    for (int start : startPositions) {
        for (int j = 0; j < m; ++j) {
            bases[start + j] = 'X';
        }
    }

    return (int)startPositions.size();
}

void Secuencia::escribirFASTA(std::ostream& os) const {
    int width = (anchoLinea > 0 ? anchoLinea : 60);
    os << ">" << descripcion << "\n";
    int n = (int)bases.size();
    for (int i = 0; i < n; i += width) {
        int len = (i + width <= n ? width : (n - i));
        os.write(bases.data() + i, len);
        os << "\n";
    }
}
