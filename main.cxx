#include <iostream>
#include <string>
#include "genoma.h"
#include "comandos.h"
#include "sistema.h"
using namespace std;



int main() {
    Sistema sistema;  // En lugar de Genoma genoma
    string linea;

    cout << "$ ";
    while (true) {
        if (!getline(cin, linea)) break;
        bool debeSalir = procesarLinea(linea, sistema);  // Pasar sistema
        if (debeSalir) break;
        cout << "$ ";
    }
    return 0;
}
