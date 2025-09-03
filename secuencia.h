#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <string>
#include <iostream>

class Secuencia {
public:
    std::string descripcion;
    std::string bases;     // concatenada sin saltos
    int anchoLinea;        // ancho original de justificacion (>=0)

    Secuencia();

    bool esCompleta() const;// true si no tiene '-'
    int  contarBasesValidas() const;// sin contar '-'

    // Histograma en el orden A C G T U R Y K M S W B D H V N X -
    int  histograma(int outFreq[18]) const;

    int  contarSubsecuencia(const std::string& sub) const;// Cuenta apariciones con equivalencias

    // Enmascara con 'X' 
    int  enmascararSubsecuencia(const std::string& sub);

    void escribirFASTA(std::ostream& os) const;// escribe en formato FASTA
};

#endif
