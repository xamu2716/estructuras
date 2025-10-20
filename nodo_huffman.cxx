#include "nodo_huffman.h"

NodoHuffman::NodoHuffman() : simbolo_(0), freq_(0ull), izq_(0), der_(0), esHoja_(false) {}

NodoHuffman::NodoHuffman(unsigned char simbolo, unsigned long long freq, bool esHoja)
: simbolo_(simbolo), freq_(freq), izq_(0), der_(0), esHoja_(esHoja) {}

unsigned char NodoHuffman::simbolo() const { return simbolo_; }
unsigned long long NodoHuffman::freq() const { return freq_; }
NodoHuffman* NodoHuffman::izq() const { return izq_; }
NodoHuffman* NodoHuffman::der() const { return der_; }
bool NodoHuffman::esHoja() const { return esHoja_; }

void NodoHuffman::setIzq(NodoHuffman* p) { izq_ = p; }
void NodoHuffman::setDer(NodoHuffman* p) { der_ = p; }
void NodoHuffman::setFreq(unsigned long long f) { freq_ = f; }
