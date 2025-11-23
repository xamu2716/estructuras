#include "comandos.h"
#include "utilidades.h"
#include "ayuda.h"
#include "sistema.h"
#include "grafo.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;


bool procesarLinea(const string& linea, Sistema& sistema) {
    string cmd = firstToken(linea);
    string resto = restAfterFirst(linea);
    if (cmd.empty()) return false;

    if      (cmd == "ayuda")             return cmdAyuda(resto);
    else if (cmd == "cargar")            return cmdCargar(resto, sistema);
    else if (cmd == "listar_secuencias") return cmdListar(resto, sistema);
    else if (cmd == "histograma")        return cmdHistograma(resto, sistema);
    else if (cmd == "es_subsecuencia")   return cmdEsSubsec(resto, sistema);
    else if (cmd == "enmascarar")        return cmdEnmascarar(resto, sistema);
    else if (cmd == "guardar")           return cmdGuardar(resto, sistema);
    else if (cmd == "codificar")         return cmdCodificar(resto, sistema);
    else if (cmd == "decodificar")       return cmdDecodificar(resto, sistema);
    else if (cmd == "ruta_mas_corta")    return cmdRutaMasCorta(resto, sistema);
    else if (cmd == "base_remota")       return cmdBaseRemota(resto, sistema);
    else if (cmd == "salir")             return cmdSalir();
    else {
        cout << "Comando invalido. Escriba 'ayuda' para ver opciones.\n";
        return false;
    }
}

bool cmdAyuda(const string& resto) {
    int n = countWords(resto);
    if (n == 0) { mostrarAyudaGeneral(); return false; }
    if (n == 1) { mostrarAyudaComando(firstToken(resto)); return false; }
    cout << "Uso: ayuda [comando]\n";
    return false;
}

bool cmdCargar(const string& resto, Sistema& sistema) {
    if (countWords(resto) != 1) {
        cout << "Uso: cargar <archivo>\n";
        return false;
    }
    string nombreArchivo = firstToken(resto);
    if (!sistema.cargarFASTA(nombreArchivo)) {
        cout << nombreArchivo << " no se encuentra o no puede leerse." << endl;
        return false;
    }
    int n = sistema.cantidad();
    if (n == 0) {
        cout << nombreArchivo << " no contiene ninguna secuencia." << endl;
    } else if (n == 1) {
        cout << "1 secuencia cargada correctamente desde " << nombreArchivo << " ." << endl;
    } else {
        cout << n << " secuencias cargadas correctamente desde " << nombreArchivo << " ." << endl;
    }
    return false;
}

bool cmdListar(const string& resto, Sistema& sistema) {
    if (countWords(resto) != 0) {
        cout << "Uso: listar_secuencias\n";
        return false;
    }
    int n = sistema.cantidad();
    if (n == 0) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return false;
    }
    cout << "Hay " << n << " secuencias cargadas en memoria:\n";

    const std::vector<Secuencia>& ref = sistema.datos();
    for (size_t i = 0; i < ref.size(); ++i) {
        const Secuencia& seq = ref[i];
        int basesValidas = seq.contarBasesValidas();
        if (seq.esCompleta()) {
            cout << "Secuencia " << seq.descripcion << " contiene " << basesValidas << " bases." << endl;
        } else {
            cout << "Secuencia " << seq.descripcion << " contiene al menos " << basesValidas << " bases." << endl;
        }
    }
    return false;
}

bool cmdHistograma(const string& resto, Sistema& sistema) {
    if (countWords(resto) != 1) {
        cout << "Uso: histograma <descripcion_secuencia>\n";
        return false;
    }
    string nombre = firstToken(resto);
    if (sistema.cantidad() == 0) {
        cout << "Secuencia invalida.\n";
        return false;
    }
    Secuencia* s = sistema.get(nombre);
    if (s == 0) {
        cout << "Secuencia invalida.\n";
        return false;
    }
    int f[18]; s->histograma(f);
    const char* label[18] = {
        "A","C","G","T","U","R","Y","K","M","S","W","B","D","H","V","N","X","-"
    };
    for (int i = 0; i < 18; ++i) {
        cout << label[i] << " : " << f[i] << "\n";
    }
    return false;
}

bool cmdEsSubsec(const string& resto, Sistema& sistema) {
    if (countWords(resto) != 1) {
        cout << "Uso: es_subsecuencia <subsecuencia>\n";
        return false;
    }
    if (sistema.cantidad() == 0) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return false;
    }
    string sub = firstToken(resto);
    int s = sistema.contarSubseqGlobal(sub);
    if (s == 0) {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria.\n";
    } else if (s == 1) {
        cout << "La subsecuencia dada se repite 1 vez dentro de las secuencias cargadas en memoria.\n";
    } else {
        cout << "La subsecuencia dada se repite " << s << " veces dentro de las secuencias cargadas en memoria.\n";
    }
    return false;
}

bool cmdEnmascarar(const string& resto, Sistema& sistema) {
    if (countWords(resto) != 1) {
        cout << "Uso: enmascarar <subsecuencia>\n";
        return false;
    }
    if (sistema.cantidad() == 0) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return false;
    }
    string sub = firstToken(resto);
    int s = sistema.enmascararGlobal(sub);
    if (s == 0) {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada.\n";
    } else {
        cout << s << " subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria.\n";
    }
    return false;
}

bool cmdGuardar(const string& resto, Sistema& sistema) {
    if (countWords(resto) != 1) {
        cout << "Uso: guardar <archivo>\n";
        return false;
    }
    if (sistema.cantidad() == 0) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return false;
    }
    string nombre = firstToken(resto);
    if (!sistema.guardarFASTA(nombre)) {
        cout << "Error guardando en " << nombre << " .\n";
    } else {
        cout << "Las secuencias han sido guardadas en " << nombre << " .\n";
    }
    return false;
}

bool cmdCodificar(const std::string& resto, Sistema& sistema) {
    if (countWords(resto) != 1) {
        std::cout << "Uso: codificar <nombre_archivo.fabin>\n";
        return false;
    }
    if (sistema.cantidad() == 0) {
        std::cout << "No hay secuencias cargadas en memoria.\n";
        return false;
    }
    std::string nombre = firstToken(resto);
    if (!sistema.codificarFabin(nombre)) {
        std::cout << "No se pueden guardar las secuencias cargadas en " << nombre << " .\n";
    } else {
        std::cout << "Secuencias codificadas y almacenadas en " << nombre << " .\n";
    }
    return false;
}

bool cmdDecodificar(const std::string& resto, Sistema& sistema) {
    if (countWords(resto) != 1) {
        std::cout << "Uso: decodificar <nombre_archivo.fabin>\n";
        return false;
    }
    std::string nombre = firstToken(resto);
    if (!sistema.decodificarFabin(nombre)) {
        std::cout << "No se pueden cargar las secuencias desde " << nombre << " .\n";
    } else {
        std::cout << "Secuencias decodificadas desde " << nombre << " y cargadas en memoria.\n";
    }
    return false;
}
bool cmdRutaMasCorta(const std::string& resto, Sistema& sistema) {
    istringstream ss(resto);
    string nombre;
    int i, j, x, y;

    if (!(ss >> nombre >> i >> j >> x >> y)) {
        cout << "Uso: ruta_mas_corta <nombre> i j x y\n";
        return false;
    }

    Secuencia* s = sistema.get(nombre);
    if (!s) {
        cout << "Secuencia no existe.\n";
        return false;
    }

    Grafo g(s);
    int n1 = g.nodoDesdeCoordenadas(i, j);
    int n2 = g.nodoDesdeCoordenadas(x, y);

    if (n1 < 0 || n2 < 0) {
        cout << "Coordenadas invalidas.\n";
        return false;
    }

    vector<double> dist;
    vector<int> padre;
    g.dijkstra(n1, dist, padre);

    if (padre[n2] == -1 && n1 != n2) {
        cout << "No existe ruta.\n";
        return false;
    }

    vector<int> camino;
    int cur = n2;

    while (cur != -1) {
        camino.push_back(cur);
        if (cur == n1) break;
        cur = padre[cur];
    }

    std::reverse(camino.begin(), camino.end());

    cout << "Ruta mas corta:\n";
    for (size_t k = 0; k < camino.size(); k++) {
        int f, c;
        g.coordenadasDesdeNodo(camino[k], f, c);
        char base = s->bases[camino[k]];
        cout << "(" << f << "," << c << ")[" << base << "]";
        if (k + 1 < camino.size()) cout << " -> ";
    }
    cout << "\nCosto total: " << dist[n2] << "\n";

    return false;
}
bool cmdBaseRemota(const std::string& resto, Sistema& sistema) {
    istringstream ss(resto);
    string nombre;
    int i, j;

    if (!(ss >> nombre >> i >> j)) {
        cout << "Uso: base_remota <nombre> i j\n";
        return false;
    }

    Secuencia* s = sistema.get(nombre);
    if (!s) {
        cout << "Secuencia no existe.\n";
        return false;
    }

    Grafo g(s);
    int origen = g.nodoDesdeCoordenadas(i, j);

    if (origen < 0) {
        cout << "Coordenadas invalidas.\n";
        return false;
    }

    char buscada = s->bases[origen];

    vector<double> dist;
    vector<int> padre;
    g.dijkstra(origen, dist, padre);

    int mejor = -1;
    double mejorDist = -1.0;

    for (int k = 0; k < (int)s->bases.size(); k++) {
        if (s->bases[k] != buscada) continue;
        if (k == origen) continue;
        if (padre[k] == -1) continue;

        if (dist[k] > mejorDist) {
            mejorDist = dist[k];
            mejor = k;
        }
    }

    if (mejor == -1) {
        cout << "No existe otra base igual alcanzable.\n";
        return false;
    }

    vector<int> camino;
    int cur = mejor;

    while (cur != -1) {
        camino.push_back(cur);
        if (cur == origen) break;
        cur = padre[cur];
    }

    std::reverse(camino.begin(), camino.end());

    int f, c;
    g.coordenadasDesdeNodo(mejor, f, c);

    cout << "Base remota mas lejana '" << buscada << "': (" << f << "," << c << ")\n";
    cout << "Ruta:\n";

    for (size_t k = 0; k < camino.size(); k++) {
        g.coordenadasDesdeNodo(camino[k], f, c);
        cout << "(" << f << "," << c << ")[" << s->bases[camino[k]] << "]";
        if (k + 1 < camino.size()) cout << " -> ";
    }
    cout << "\nCosto total: " << mejorDist << "\n";

    return false;
}

bool cmdSalir() { return true; }
