#include "comandos.h"
#include "utilidades.h"
#include "ayuda.h"
#include <iostream>

using namespace std;

bool procesarLinea(const string& linea) {
    string cmd = firstToken(linea);
    string resto = restAfterFirst(linea);

    if (cmd.empty()) return false;

    if (cmd == "ayuda")                  return cmdAyuda(resto);
    else if (cmd == "cargar")            return cmdCargar(resto);
    else if (cmd == "listar_secuencias") return cmdListar(resto);
    else if (cmd == "histograma")        return cmdHistograma(resto);
    else if (cmd == "es_subsecuencia")   return cmdEsSubsec(resto);
    else if (cmd == "enmascarar")        return cmdEnmascarar(resto);
    else if (cmd == "guardar")           return cmdGuardar(resto);
    else if (cmd == "codificar")         return cmdCodificar(resto);
    else if (cmd == "decodificar")       return cmdDecodificar(resto);
    else if (cmd == "ruta_mas_corta")    return cmdRutaMasCorta(resto);
    else if (cmd == "base_remota")       return cmdBaseRemota(resto);
    else if (cmd == "salir")             return cmdSalir();
    else {
        cout << "Comando invalido.\n";
        return false;
    }
}

bool cmdAyuda(const string& resto) {
    int n = countWords(resto);
    if (n == 0) { mostrarAyudaGeneral(); return false; }
    if (n == 1) { mostrarAyudaComando(trim(resto)); return false; }
    cout << "Uso: ayuda [comando]\n";
    return false;
}

bool cmdCargar(const string& resto) {
    int n = countWords(resto);
    if (n != 1) {
        cout << "Uso: cargar <nombre_archivo>\n";
        return false;
    }
    cout << "3 secuencias cargadas correctamente desde nombre_archivo .\n";
    return false;
}

bool cmdListar(const string& resto) {
    if (!trim(resto).empty()) {
        cout << "Uso: listar_secuencias\n";
        return false;
    }
    cout << "Hay 3 secuencias cargadas en memoria:\n";
    cout << "Secuencia Full_SEQUENCE contiene 120 bases.\n";
    cout << "Secuencia Incomplete_sequence contiene al menos 85 bases.\n";
    return false;
}

bool cmdHistograma(const string& resto) {
    int n = countWords(resto);
    if (n != 1) {
        cout << "Uso: histograma <descripcion_secuencia>\n";
        return false;
    }
    cout << "A : 30\nC : 25\nG : 28\nT : 37\n";
    return false;
}

bool cmdEsSubsec(const string& resto) {
    int n = countWords(resto);
    if (n != 1) {
        cout << "Uso: es_subsecuencia <subsecuencia>\n";
        return false;
    }
    cout << "La subsecuencia dada se repite 5 veces dentro de las secuencias cargadas en memoria.\n";
    return false;
}

bool cmdEnmascarar(const string& resto) {
    int n = countWords(resto);
    if (n != 1) {
        cout << "Uso: enmascarar <subsecuencia>\n";
        return false;
    }
    cout << "5 subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria.\n";
    return false;
}

bool cmdGuardar(const string& resto) {
    int n = countWords(resto);
    if (n != 1) {
        cout << "Uso: guardar <nombre_archivo>\n";
        return false;
    }
    cout << "Las secuencias han sido guardadas en nombre_archivo .\n";
    return false;
}

bool cmdCodificar(const string& resto) {
    int n = countWords(resto);
    string arg = trim(resto);
    if (n != 1 || !endsWith(arg, ".fabin")) {
        cout << "Uso: codificar <nombre_archivo.fabin>\n";
        return false;
    }
    cout << "Secuencias codificadas y almacenadas en nombre_archivo.fabin .\n";
    return false;
}

bool cmdDecodificar(const string& resto) {
    int n = countWords(resto);
    string arg = trim(resto);
    if (n != 1 || !endsWith(arg, ".fabin")) {
        cout << "Uso: decodificar <nombre_archivo.fabin>\n";
        return false;
    }
    cout << "Secuencias decodificadas desde nombre_archivo.fabin y cargadas en memoria.\n";
    return false;
}

bool cmdRutaMasCorta(const string& resto) {
    if (countWords(resto) != 5) {
        cout << "Uso: ruta_mas_corta <nombre> i j x y\n";
        return false;
    }
    cout << "Para la secuencia nombre, la ruta mas corta entre la base N en [i ,j ] y la base M en [x ,y ] es: AGCTTAGC . El costo total de la ruta es: 15\n";
    return false;
}

bool cmdBaseRemota(const string& resto) {
    if (countWords(resto) != 3) {
        cout << "Uso: base_remota <nombre> i j\n";
        return false;
    }
    cout << "Para la secuencia nombre, la base remota esta ubicada en [5 ,10 ] , y la ruta entre la base en [i ,j ] y la base remota en [a ,b ] es: ACTGTT . El costo total de la ruta es: 12\n";
    return false;
}

bool cmdSalir() {
    return true;
}
