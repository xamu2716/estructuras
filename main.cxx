#include <iostream>
#include <string>
#include "genoma.h"
#include "comandos.h"
#include "sistema.h"
using namespace std;



int main() {
    Sistema sistema; 
    string linea;

    cout << "$ ";
    while (true) {
        if (!getline(cin, linea)) break;
        bool debeSalir = procesarLinea(linea, sistema); 
        if (debeSalir) break;
        cout << "$ ";
    }
    return 0;
}
