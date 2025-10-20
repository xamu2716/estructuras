#include "arbol_huffman.h"

ArbolHuffman::ArbolHuffman() : raiz_(0) {}
ArbolHuffman::~ArbolHuffman() { liberar(raiz_); }

void ArbolHuffman::liberar(NodoHuffman* p) {
    if (!p) return;
    liberar(p->izq());
    liberar(p->der());
    delete p;
}

NodoHuffman* ArbolHuffman::crearHoja(unsigned char c, unsigned long long f) {
    NodoHuffman* n = new NodoHuffman(c, f, true);
    return n;
}

NodoHuffman* ArbolHuffman::crearInterno(NodoHuffman* a, NodoHuffman* b) {
    NodoHuffman* n = new NodoHuffman(0, a->freq() + b->freq(), false);
    n->setIzq(a);
    n->setDer(b);
    return n;
}

// ===== heap minimo (vector de punteros) =====
void ArbolHuffman::heapInsertar(NodoHuffman* p) {
    heap_.push_back(p);
    heapSubir(heap_.size() - 1);
}

NodoHuffman* ArbolHuffman::heapExtraerMin() {
    if (heap_.empty()) return 0;
    NodoHuffman* ans = heap_[0];
    heap_[0] = heap_.back();
    heap_.pop_back();
    heapBajar(0);
    return ans;
}

void ArbolHuffman::heapSubir(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap_[idx]->freq() < heap_[parent]->freq()) {
            NodoHuffman* tmp = heap_[idx];
            heap_[idx] = heap_[parent];
            heap_[parent] = tmp;
            idx = parent;
        } else {
            break;
        }
    }
}

void ArbolHuffman::heapBajar(int idx) {
    int n = heap_.size();
    while (true) {
        int li = idx * 2 + 1;
        int ri = idx * 2 + 2;
        int smallest = idx;
        if (li < n && heap_[li]->freq() < heap_[smallest]->freq()) smallest = li;
        if (ri < n && heap_[ri]->freq() < heap_[smallest]->freq()) smallest = ri;
        if (smallest != idx) {
            NodoHuffman* tmp = heap_[idx];
            heap_[idx] = heap_[smallest];
            heap_[smallest] = tmp;
            idx = smallest;
        } else {
            break;
        }
    }
}

// ===== construir arbol =====
bool ArbolHuffman::construir(const std::vector< std::pair<unsigned char, unsigned long long> >& pares) {
    liberar(raiz_);
    raiz_ = 0;
    heap_.clear();

    int i;
    for (i = 0; i < pares.size(); ++i) {
        if (pares[(size_t)i].second == 0ull) continue;
        NodoHuffman* hoja = crearHoja(pares[(size_t)i].first, pares[(size_t)i].second);
        heapInsertar(hoja);
    }
    if (heap_.empty()) return false;

    if (heap_.size() == 1u) {
        raiz_ = heapExtraerMin();
        return true;
    }

    while (heap_.size() > 1u) {
        NodoHuffman* a = heapExtraerMin();
        NodoHuffman* b = heapExtraerMin();
        NodoHuffman* p = crearInterno(a, b);
        heapInsertar(p);
    }
    raiz_ = heapExtraerMin();
    return raiz_ != 0;
}

void ArbolHuffman::construirCodigos(NodoHuffman* p, std::string prefijo, std::map<unsigned char, std::string>& outCodes) const {
    if (!p) return;
    if (p->esHoja()) {
        if (prefijo.empty()) prefijo = "0";
        outCodes[p->simbolo()] = prefijo;
        return;
    }
    construirCodigos(p->izq(), prefijo + "0", outCodes);
    construirCodigos(p->der(), prefijo + "1", outCodes);
}

void ArbolHuffman::generarCodigos(std::map<unsigned char, std::string>& outCodes) const {
    outCodes.clear();
    construirCodigos(raiz_, "", outCodes);
}

bool ArbolHuffman::esValido() const { return raiz_ != 0; }

std::string ArbolHuffman::decodificar(const std::vector<unsigned char>& bits, unsigned long long bitCount) const {
    std::string salida;
    if (!raiz_) return salida;

    unsigned long long totalBits = bitCount;
    unsigned long long idxBit = 0ull;
    NodoHuffman* p = raiz_;

    while (idxBit < totalBits) {
        unsigned long long byteIndex = idxBit / 8ull;
        int bitIndex = 7 - (idxBit % 8ull);
        unsigned char byte = bits[(size_t)byteIndex];
        int bit = ((byte >> bitIndex) & 1);

        if (p->esHoja()) {
            salida.push_back(p->simbolo());
            p = raiz_;
        } else {
            if (bit == 0) p = p->izq();
            else          p = p->der();
            idxBit++;
            if (!p) break;
        }
    }
    if (p && p->esHoja()) {
        salida.push_back(p->simbolo());
    }
    return salida;
}
