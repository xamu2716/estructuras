#ifndef ARBOL_HUFFMAN_H
#define ARBOL_HUFFMAN_H

#include <string>
#include <vector>
#include <map>
#include "nodo_huffman.h"

class ArbolHuffman {
private:
    NodoHuffman* raiz_;
    std::vector<NodoHuffman*> heap_; // min-heap por frecuencia

    // memoria y codigos
    void liberar(NodoHuffman* p);
    void construirCodigos(NodoHuffman* p, std::string prefijo, std::map<unsigned char, std::string>& outCodes) const;

    // fabricas
    NodoHuffman* crearHoja(unsigned char c, unsigned long long f);// crea un nodo hoja
    NodoHuffman* crearInterno(NodoHuffman* a, NodoHuffman* b);// crea un nodo interno

    // heap minimo
    void heapInsertar(NodoHuffman* p);// inserta un nodo en el heap
    NodoHuffman* heapExtraerMin();// extrae el minimo del heap
    void heapSubir(int idx);// sube un nodo en el heap
    void heapBajar(int idx);// baja un nodo en el heap

public:
    ArbolHuffman();
    ~ArbolHuffman();

    bool construir(const std::vector< std::pair<unsigned char, unsigned long long> >& pares);
    void generarCodigos(std::map<unsigned char, std::string>& outCodes) const;// genera los codigos de Huffman
    bool esValido() const;// true si el arbol es valido
    std::string decodificar(const std::vector<unsigned char>& bits, unsigned long long bitCount) const;// decodifica un stream de bits
};

#endif
