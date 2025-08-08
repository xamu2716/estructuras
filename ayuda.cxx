#include "ayuda.h"
#include <iostream>
#include <string>

using namespace std;

void mostrarAyudaGeneral() {
    cout << "Comandos disponibles:\n";
    cout << "  ayuda                  -> Muestra esta lista de comandos\n";
    cout << "  ayuda <comando>        -> Muestra ayuda especifica para un comando\n";
    cout << "  cargar <archivo>       -> Carga un archivo FASTA en memoria\n";
    cout << "  listar_secuencias      -> Lista las secuencias en memoria\n";
    cout << "  histograma <nombre>    -> Muestra la frecuencia de bases en una secuencia\n";
    cout << "  es_subsecuencia <sub>  -> Verifica si una subsecuencia esta en las secuencias cargadas\n";
    cout << "  enmascarar <sub>       -> Enmascara la subsecuencia en las secuencias cargadas\n";
    cout << "  guardar <archivo>      -> Guarda las secuencias en un archivo\n";
    cout << "  codificar <archivo>    -> Simula la codificacion de las secuencias en un archivo\n";
    cout << "  decodificar <archivo>  -> Simula la lectura y carga de secuencias desde un archivo\n";
    cout << "  ruta_mas_corta <nombre> i j x y -> Simula una ruta entre dos posiciones\n";
    cout << "  base_remota <nombre> i j       -> Simula la busqueda de una base igual mas lejana\n";
    cout << "  salir                  -> Termina el programa\n";
}

void mostrarAyudaComando(const string& comando) {
    if (comando == "cargar") {
        cout << "Uso: cargar <nombre_archivo>\n";
        cout << "Descripcion: Carga en memoria las secuencias de un archivo FASTA.\n";
    } else if (comando == "listar_secuencias") {
        cout << "Uso: listar_secuencias\n";
        cout << "Descripcion: Muestra todas las secuencias en memoria.\n";
    } else if (comando == "histograma") {
        cout << "Uso: histograma <descripcion_secuencia>\n";
        cout << "Descripcion: Muestra la frecuencia de cada base en la secuencia indicada.\n";
    } else if (comando == "es_subsecuencia") {
        cout << "Uso: es_subsecuencia <subsecuencia>\n";
        cout << "Descripcion: Verifica si la subsecuencia aparece en las secuencias cargadas.\n";
    } else if (comando == "enmascarar") {
        cout << "Uso: enmascarar <subsecuencia>\n";
        cout << "Descripcion: Reemplaza la subsecuencia por 'X' en todas sus apariciones.\n";
    } else if (comando == "guardar") {
        cout << "Uso: guardar <nombre_archivo>\n";
        cout << "Descripcion: Guarda las secuencias en memoria en un archivo FASTA.\n";
    } else if (comando == "codificar") {
        cout << "Uso: codificar <nombre_archivo.fabin>\n";
        cout << "Descripcion: Simula la codificacion de las secuencias en un archivo.\n";
    } else if (comando == "decodificar") {
        cout << "Uso: decodificar <nombre_archivo.fabin>\n";
        cout << "Descripcion: Simula la lectura y carga de secuencias desde un archivo codificado.\n";
    } else if (comando == "ruta_mas_corta") {
        cout << "Uso: ruta_mas_corta <nombre> i j x y\n";
        cout << "Descripcion: Simula la ruta entre dos posiciones en una secuencia.\n";
    } else if (comando == "base_remota") {
        cout << "Uso: base_remota <nombre> i j\n";
        cout << "Descripcion: Simula la busqueda de una base igual mas lejana desde una posicion.\n";
    } else if (comando == "salir") {
        cout << "Uso: salir\n";
        cout << "Descripcion: Cierra el programa.\n";
    } else if (comando == "ayuda") {
        cout << "Uso: ayuda [comando]\n";
        cout << "Descripcion: Muestra esta lista o la ayuda especifica de un comando.\n";
    } else {
        cout << "No hay ayuda disponible para el comando: " << comando << "\n";
    }
}