#include "../../include/Estructuras/EstructProfe.h"
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

ArbolProfesores::ArbolProfesores() : raiz(nullptr) {}

ArbolProfesores::~ArbolProfesores() {
    destruirRec(raiz);
}

void ArbolProfesores::destruirRec(NodoProfesor* nodo) {
    if (nodo) {
        destruirRec(nodo->izq);
        destruirRec(nodo->der);
        delete nodo;
    }
}

void ArbolProfesores::insertar(Profesor p) {
    insertarRec(raiz, p);
}

void ArbolProfesores::insertarRec(NodoProfesor*& nodo, Profesor p) {
    if (nodo == nullptr) {
        nodo = new NodoProfesor(p);
    } else {
        if (p.getBoletaTrabajador() < nodo->dato.getBoletaTrabajador()) {
            insertarRec(nodo->izq, p);
        } else {
            insertarRec(nodo->der, p);
        }
    }
}

Profesor* ArbolProfesores::buscar(string boleta) {
    NodoProfesor* actual = raiz;
    while (actual != nullptr) {
        if (boleta == actual->dato.getBoletaTrabajador()) {
            return &actual->dato; 
        }
        else if (boleta < actual->dato.getBoletaTrabajador()) {
            actual = actual->izq;
        }
        else {
            actual = actual->der;
        }
    }
    return nullptr;
}

void ArbolProfesores::listar() {
    cout << "--- LISTA DE PROFESORES (Ordenada por Boleta) ---" << endl;
    if (!raiz) cout << "(Vacio)" << endl;
    else listarRec(raiz);
}

void ArbolProfesores::listarRec(NodoProfesor* nodo) {
    if (nodo) {
        listarRec(nodo->izq);
        cout << "[" << nodo->dato.getBoletaTrabajador() << "] "
             << nodo->dato.getNombreCompleto()
             << " | Titular: " << nodo->dato.getIdGrupoTitular() << endl;
        listarRec(nodo->der);
    }
}

// --- PERSISTENCIA JSON ---

void ArbolProfesores::guardarEnArchivo() {
    #ifdef _WIN32
        _mkdir("Data");
    #else
        mkdir("Data", 0777);
    #endif

    ofstream archivo("Data/profesores.json");
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo crear el archivo Data/profesores.json" << endl;
        return;
    }

    archivo << "[\n";
    bool primero = true;
    guardarRec(raiz, archivo, primero);
    archivo << "\n]";
    archivo.close();
}

void ArbolProfesores::guardarRec(NodoProfesor* nodo, ofstream& archivo, bool& primero) {
    if (nodo) {
        if (!primero) {
            archivo << ",\n";
        }

        archivo << "  {\n";
        archivo << "    \"boleta\": \"" << nodo->dato.getBoletaTrabajador() << "\",\n";
        archivo << "    \"nombre\": \"" << nodo->dato.getNombreCompleto() << "\",\n";
        archivo << "    \"telefono\": \"" << nodo->dato.getTelefono() << "\",\n";
        archivo << "    \"titularDe\": \"" << nodo->dato.getIdGrupoTitular() << "\",\n";
        archivo << "    \"gruposAsignados\": \"" << nodo->dato.getGruposAsignados() << "\"\n";
        archivo << "  }";

        primero = false;

        guardarRec(nodo->izq, archivo, primero);
        guardarRec(nodo->der, archivo, primero);
    }
}

string ArbolProfesores::extraerValorJson(string linea) {
    size_t posDosPuntos = linea.find(':');
    if (posDosPuntos == string::npos) return "";
    string valor = linea.substr(posDosPuntos + 1);
    size_t firstQuote = valor.find('\"');
    size_t lastQuote = valor.rfind('\"');
    if (firstQuote != string::npos && lastQuote != string::npos && lastQuote > firstQuote) {
        return valor.substr(firstQuote + 1, lastQuote - firstQuote - 1);
    }
    return "";
}

void ArbolProfesores::cargarDeArchivo() {
    ifstream archivo("Data/profesores.json"); // Ruta actualizada
    if (!archivo.is_open()) return;

    string linea;
    Profesor pActual;
    bool leyendoObjeto = false;

    while (getline(archivo, linea)) {
        if (linea.find("{") != string::npos) {
            leyendoObjeto = true;
            pActual = Profesor();
        }
        else if (linea.find("}") != string::npos && leyendoObjeto) {
            insertar(pActual);
            leyendoObjeto = false;
        }
        else if (leyendoObjeto) {
            if (linea.find("\"boleta\"") != string::npos)
                pActual.setBoletaTrabajador(extraerValorJson(linea));
            else if (linea.find("\"nombre\"") != string::npos)
                pActual.setNombreCompleto(extraerValorJson(linea));
            else if (linea.find("\"telefono\"") != string::npos)
                pActual.setTelefono(extraerValorJson(linea));
            else if (linea.find("\"titularDe\"") != string::npos)
                pActual.setIdGrupoTitular(extraerValorJson(linea));
            else if (linea.find("\"gruposAsignados\"") != string::npos)
                pActual.setGruposAsignados(extraerValorJson(linea));
        }
    }
    archivo.close();
}