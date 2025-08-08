#include <iostream>
#include <string>
#include "comandos.h"
using namespace std;

int main() {
    string linea;
    cout << "$ ";
    while (getline(cin, linea)) {
        bool terminar = procesarLinea(linea);
        if (terminar) break;
        cout << "$ ";
    }
    return 0;
}
