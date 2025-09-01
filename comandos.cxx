#include "comandos.h"
#include "utilidades.h"
#include "ayuda.h"
#include "genoma.h"

#include <iostream>
#include <fstream>
using namespace std;

bool procesarLinea(const string& linea, Genoma& genoma) {
    string cmd = firstToken(linea);
    string resto = restAfterFirst(linea);
    if (cmd.empty()) return false;

    if      (cmd == "ayuda")             return cmdAyuda(resto);
    else if (cmd == "cargar")            return cmdCargar(resto, genoma);
    else if (cmd == "listar_secuencias") return cmdListar(resto, genoma);
    else if (cmd == "histograma")        return cmdHistograma(resto, genoma);
    else if (cmd == "es_subsecuencia")   return cmdEsSubsec(resto, genoma);
    else if (cmd == "enmascarar")        return cmdEnmascarar(resto, genoma);
    else if (cmd == "guardar")           return cmdGuardar(resto, genoma);
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

bool cmdCargar(const string& resto, Genoma& genoma) {
    if (countWords(resto) != 1) {
        cout << "Uso: cargar <archivo>\n";
        return false;
    }
    string nombreArchivo = firstToken(resto);
    if (!genoma.cargarFASTA(nombreArchivo)) {
        cout << nombreArchivo << " no se encuentra o no puede leerse." << endl;
        return false;
    }
    int n = genoma.cantidad();
    if (n == 0) {
        cout << nombreArchivo << " no contiene ninguna secuencia." << endl;
    } else if (n == 1) {
        cout << "1 secuencia cargada correctamente desde " << nombreArchivo << " ." << endl;
    } else {
        cout << n << " secuencias cargadas correctamente desde " << nombreArchivo << " ." << endl;
    }
    return false;
}

bool cmdListar(const string& resto, Genoma& genoma) {
    if (countWords(resto) != 0) {
        cout << "Uso: listar_secuencias\n";
        return false;
    }
    int n = genoma.cantidad();
    if (n == 0) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return false;
    }
    cout << "Hay " << n << " secuencias cargadas en memoria:\n";

    const std::vector<Secuencia>& ref = genoma.datos();
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

bool cmdHistograma(const string& resto, Genoma& genoma) {
    if (countWords(resto) != 1) {
        cout << "Uso: histograma <descripcion_secuencia>\n";
        return false;
    }
    string nombre = firstToken(resto);
    if (genoma.cantidad() == 0) {
        cout << "Secuencia invalida.\n";
        return false;
    }
    Secuencia* s = genoma.get(nombre);
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

bool cmdEsSubsec(const string& resto, Genoma& genoma) {
    if (countWords(resto) != 1) {
        cout << "Uso: es_subsecuencia <subsecuencia>\n";
        return false;
    }
    if (genoma.cantidad() == 0) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return false;
    }
    string sub = firstToken(resto);
    int s = genoma.contarSubseqGlobal(sub);
    if (s == 0) {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria.\n";
    } else if (s == 1) {
        cout << "La subsecuencia dada se repite 1 vez dentro de las secuencias cargadas en memoria.\n";
    } else {
        cout << "La subsecuencia dada se repite " << s << " veces dentro de las secuencias cargadas en memoria.\n";
    }
    return false;
}

bool cmdEnmascarar(const string& resto, Genoma& genoma) {
    if (countWords(resto) != 1) {
        cout << "Uso: enmascarar <subsecuencia>\n";
        return false;
    }
    if (genoma.cantidad() == 0) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return false;
    }
    string sub = firstToken(resto);
    int s = genoma.enmascararGlobal(sub);
    if (s == 0) {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada.\n";
    } else {
        cout << s << " subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria.\n";
    }
    return false;
}

bool cmdGuardar(const string& resto, Genoma& genoma) {
    if (countWords(resto) != 1) {
        cout << "Uso: guardar <archivo>\n";
        return false;
    }
    if (genoma.cantidad() == 0) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return false;
    }
    string nombre = firstToken(resto);
    if (!genoma.guardarFASTA(nombre)) {
        cout << "Error guardando en " << nombre << " .\n";
    } else {
        cout << "Las secuencias han sido guardadas en " << nombre << " .\n";
    }
    return false;
}

bool cmdSalir() { return true; }
