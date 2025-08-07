#include <iostream>
#include <string>
#include <list>

using namespace std;

bool validarParametros(const string &comando, int cantidad)
{
    if (comando == "cargar" && cantidad != 1)
        return false;
    if (comando == "listar_secuencias" && cantidad != 0)
        return false;
    if (comando == "histograma" && cantidad != 1)
        return false;
    if (comando == "es_subsecuencia" && cantidad != 1)
        return false;
    if (comando == "enmascarar" && cantidad != 1)
        return false;
    if (comando == "guardar" && cantidad != 1)
        return false;
    if (comando == "codificar" && cantidad != 1)
        return false;
    if (comando == "decodificar" && cantidad != 1)
        return false;
    if (comando == "ruta_mas_corta" && cantidad != 5)
        return false;
    if (comando == "base_remota" && cantidad != 3)
        return false;

    return true; // Si el comando es válido y la cantidad coincide
}

// Divide una línea en palabras usando espacios como separadores
list<string> dividirPalabras(const string &linea)
{
    list<string> palabras;
    string palabra = "";

    for (char c : linea)
    {
        if (c == ' ')
        {
            if (!palabra.empty())
            {
                palabras.push_back(palabra);
                palabra.clear();
            }
        }
        else
        {
            palabra += c;
        }
    }

    if (!palabra.empty())
    {
        palabras.push_back(palabra);
    }

    return palabras;
}

void mostrarPrompt()
{
    cout << "$ ";
}

void mostrarAyudaGeneral()
{
    cout << "Comandos disponibles:\n"
         << "  cargar <archivo>\n"
         << "  listar_secuencias\n"
         << "  histograma <nombre_secuencia>\n"
         << "  es_subsecuencia <subsecuencia>\n"
         << "  enmascarar <subsecuencia>\n"
         << "  guardar <archivo>\n"
         << "  codificar <archivo>\n"
         << "  decodificar <archivo>\n"
         << "  ruta_mas_corta <nombre> <i> <j> <x> <y>\n"
         << "  base_remota <nombre> <i> <j>\n"
         << "  ayuda [comando]\n"
         << "  salir\n";
}

void mostrarAyudaEspecifica(const string &comando)
{
    if (comando == "cargar")
        cout << "Uso: cargar <archivo>\n";
    else if (comando == "listar_secuencias")
        cout << "Uso: listar_secuencias\n";
    else if (comando == "histograma")
        cout << "Uso: histograma <nombre_secuencia>\n";
    else if (comando == "es_subsecuencia")
        cout << "Uso: es_subsecuencia <subsecuencia>\n";
    else if (comando == "enmascarar")
        cout << "Uso: enmascarar <subsecuencia>\n";
    else if (comando == "guardar")
        cout << "Uso: guardar <archivo>\n";
    else if (comando == "codificar")
        cout << "Uso: codificar <archivo>\n";
    else if (comando == "decodificar")
        cout << "Uso: decodificar <archivo>\n";
    else if (comando == "ruta_mas_corta")
        cout << "Uso: ruta_mas_corta <nombre> <i> <j> <x> <y>\n";
    else if (comando == "base_remota")
        cout << "Uso: base_remota <nombre> <i> <j>\n";
    else if (comando == "ayuda")
        cout << "Uso: ayuda [comando]\n";
    else if (comando == "salir")
        cout << "Uso: salir\n";
    else
        cout << "Comando no válido para ayuda.\n";
}

int main()
{
    string linea;

    while (true)
    {
        mostrarPrompt();
        getline(cin, linea);

        list<string> palabras = dividirPalabras(linea);
        if (palabras.empty())
            continue;

        string comando = palabras.front();
        palabras.pop_front(); // quitamos el comando

        if (comando == "salir")
        {
            break;
        }
        else if (comando == "ayuda")
        {
            if (palabras.empty())
            {
                mostrarAyudaGeneral();
            }
            else
            {
                mostrarAyudaEspecifica(palabras.front());
            }
        }
        else if (
            comando == "cargar" || comando == "listar_secuencias" ||
            comando == "histograma" || comando == "es_subsecuencia" ||
            comando == "enmascarar" || comando == "guardar" ||
            comando == "codificar" || comando == "decodificar" ||
            comando == "ruta_mas_corta" || comando == "base_remota")
        {
            int cantidadParametros = palabras.size();
            if (!validarParametros(comando, cantidadParametros))
            {
                cout << "Error: número incorrecto de parámetros para \"" << comando << "\".\n";
            }
            else
            {
                cout << "Simulación: comando \"" << comando << "\" ejecutado correctamente.\n";
            }
        }
        else
        {
            cout << "Comando no reconocido.\n";
        }
    }

    return 0;
}
