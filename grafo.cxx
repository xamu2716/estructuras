#include "grafo.h"
#include <limits>
#include <cmath>

//////////////////////////////////////////////////////////////
//  COLA MINIMA AUXILIAR INTERNA 
//////////////////////////////////////////////////////////////

struct ColaMin {
    std::vector<int> nodos;      // heap
    std::vector<double> costos;  // pesos
    std::vector<int> pos;        // pos[nodo] en heap

    ColaMin(int capacidad) {
        pos.assign(capacidad, -1);
        nodos.reserve(capacidad);
        costos.reserve(capacidad);
    }

    bool vacia() const {
        return nodos.empty();
    }

    void intercambiar(int i, int j) {
        int ni = nodos[i];
        int nj = nodos[j];
        double ci = costos[i];
        double cj = costos[j];

        nodos[i] = nj;
        nodos[j] = ni;
        costos[i] = cj;
        costos[j] = ci;

        pos[ni] = j;
        pos[nj] = i;
    }

    void flotar(int idx) {
        while (idx > 0) {
            int padre = (idx - 1) / 2;
            if (costos[idx] < costos[padre]) {
                intercambiar(idx, padre);
                idx = padre;
            } else break;
        }
    }

    void hundir(int idx) {
        int n = nodos.size();
        while (true) {
            int h1 = 2 * idx + 1;
            int h2 = 2 * idx + 2;
            int menor = idx;

            if (h1 < n && costos[h1] < costos[menor]) menor = h1;
            if (h2 < n && costos[h2] < costos[menor]) menor = h2;

            if (menor != idx) {
                intercambiar(idx, menor);
                idx = menor;
            } else break;
        }
    }

    void insertar(int nodo, double costo) {
        if (nodo < 0 || nodo >= (int)pos.size()) return;
        if (pos[nodo] != -1) return; // ya está

        int idx = nodos.size();
        nodos.push_back(nodo);
        costos.push_back(costo);
        pos[nodo] = idx;
        flotar(idx);
    }

    void disminuir(int nodo, double nuevo) {
        int idx = pos[nodo];
        if (idx == -1) return;        
        if (nuevo >= costos[idx]) return;

        costos[idx] = nuevo;
        flotar(idx);
    }

    bool extraerMin(int &nodo, double &costo) {
        if (nodos.empty()) return false;

        nodo = nodos[0];
        costo = costos[0];

        int ult = nodos.size() - 1;
        int nu = nodos[ult];
        double cu = costos[ult];

        // mover último al frente
        nodos[0] = nu;
        costos[0] = cu;
        pos[nu] = 0;

        nodos.pop_back();
        costos.pop_back();
        pos[nodo] = -1;

        if (!nodos.empty()) hundir(0);
        return true;
    }
};

//////////////////////////////////////////////////////////////
//  TAD GRAFO
//////////////////////////////////////////////////////////////

Grafo::Grafo(const Secuencia* s) {
    sec = s;
    if (!sec) return;

    int n = sec->bases.size();
    columnas_ = sec->anchoLinea;
    if (columnas_ <= 0) columnas_ = n;

    nodos_ = n;
    filas_ = (n + columnas_ - 1) / columnas_;

    ady.assign(nodos_, std::vector<int>());
    peso.assign(nodos_, std::vector<double>());

    for (int id = 0; id < nodos_; id++) {
        int fila = id / columnas_;
        int col  = id % columnas_;

        // derecha
        if (col + 1 < columnas_) {
            int d = id + 1;
            if (d < nodos_) {
                agregarArista(id, d);
                agregarArista(d, id);
            }
        }

        // abajo
        if (fila + 1 < filas_) {
            int d = id + columnas_;
            if (d < nodos_) {
                agregarArista(id, d);
                agregarArista(d, id);
            }
        }
    }
}

void Grafo::agregarArista(int o, int d) {
    char a = sec->bases[o];
    char b = sec->bases[d];
    int dif = (a > b ? a - b : b - a);
    double w = 1.0 / (1.0 + dif);

    ady[o].push_back(d);
    peso[o].push_back(w);
}

int Grafo::nodoDesdeCoordenadas(int fila1, int col1) const {
    int f = fila1 - 1;
    int c = col1 - 1;

    int id = f * columnas_ + c;
    if (id < 0 || id >= nodos_) return -1;
    return id;
}

void Grafo::coordenadasDesdeNodo(int id, int &fila1, int &col1) const {
    fila1 = id / columnas_ + 1;
    col1  = id % columnas_ + 1;
}

void Grafo::dijkstra(int origen, std::vector<double>& dist, std::vector<int>& padre) const {
    dist.assign(nodos_, std::numeric_limits<double>::max());
    padre.assign(nodos_, -1);

    ColaMin cola(nodos_);

    dist[origen] = 0.0;
    cola.insertar(origen, 0.0);

    while (!cola.vacia()) {
        int u;
        double du;
        cola.extraerMin(u, du);

        if (du > dist[u]) continue;

        for (size_t k = 0; k < ady[u].size(); k++) {
            int v = ady[u][k];
            double w = peso[u][k];
            double nd = dist[u] + w;

            if (nd < dist[v]) {
                dist[v] = nd;
                padre[v] = u;
                cola.disminuir(v, nd);
                cola.insertar(v, nd);
            }
        }
    }
}
