#ifndef NODO_HUFFMAN_H
#define NODO_HUFFMAN_H

class NodoHuffman {
private:
    unsigned char simbolo_;
    unsigned long long freq_;
    NodoHuffman* izq_;
    NodoHuffman* der_;
    bool esHoja_;

public:
    NodoHuffman();
    NodoHuffman(unsigned char simbolo, unsigned long long freq, bool esHoja);

    // getters
    unsigned char simbolo() const;
    unsigned long long freq() const;
    NodoHuffman* izq() const;
    NodoHuffman* der() const;
    bool esHoja() const;

    // setters
    void setIzq(NodoHuffman* p);
    void setDer(NodoHuffman* p);
    void setFreq(unsigned long long f);
};

#endif
