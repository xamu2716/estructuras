#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include "secuencia.h"

class Grafo {
private:
    const Secuencia* sec;

    int filas_;
    int columnas_;
    int nodos_;

    std::vector< std::vector<int> > ady;
    std::vector< std::vector<double> > peso;

    void agregarArista(int o, int d);

public:
    Grafo(const Secuencia* s);

    int nodoDesdeCoordenadas(int fila1, int col1) const;
    void coordenadasDesdeNodo(int id, int &fila1, int &col1) const;

    void dijkstra(int origen, std::vector<double>& dist, std::vector<int>& padre) const;
};

#endif
