#include <iostream>
#include <string>
#include "genoma.h"
#include "comandos.h"

using namespace std;

int main() {
    Genoma genoma;             // instancia unica del estado en memoria
    string linea;

    cout << "$ ";
    while (true) {
        if (!getline(cin, linea)) {
            break; // EOF o error de entrada
        }
        bool debeSalir = procesarLinea(linea, genoma);
        if (debeSalir) {
            break;
        }
        cout << "$ ";
    }
    return 0;
}
