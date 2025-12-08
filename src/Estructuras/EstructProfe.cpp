#include "../../include/Estructuras/EstructProfe.h"

// Constructor
ArbolProfesores::ArbolProfesores() : raiz(nullptr) {}

// Destructor
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

// --- INSERTAR (Lógica de Árbol Binario de Búsqueda) ---
void ArbolProfesores::insertar(Profesor p) {
    insertarRec(raiz, p);
}

void ArbolProfesores::insertarRec(NodoProfesor*& nodo, Profesor p) {
    if (nodo == nullptr) {
        nodo = new NodoProfesor(p);
    } else {
        // Ordenamos por boletaTrabajador alfabéticamente/numéricamente
        if (p.getBoletaTrabajador() < nodo->dato.getBoletaTrabajador()) {
            insertarRec(nodo->izq, p);
        } else {
            insertarRec(nodo->der, p);
        }
    }
}

// --- BUSCAR (Búsqueda Binaria) ---
Profesor* ArbolProfesores::buscar(string boleta) {
    NodoProfesor* actual = raiz;
    while (actual != nullptr) {
        if (boleta == actual->dato.getBoletaTrabajador()) {
            return &actual->dato; // Encontrado
        }
        else if (boleta < actual->dato.getBoletaTrabajador()) {
            actual = actual->izq;
        }
        else {
            actual = actual->der;
        }
    }
    return nullptr; // No encontrado
}

// --- LISTAR (In-Order: Imprime ordenado) ---
void ArbolProfesores::listar() {
    cout << "--- LISTA DE PROFESORES (Ordenada por Boleta) ---" << endl;
    if (!raiz) cout << "(Vacio)" << endl;
    else listarRec(raiz);
}

void ArbolProfesores::listarRec(NodoProfesor* nodo) {
    if (nodo) {
        listarRec(nodo->izq);
        // Mostrar datos relevantes incluyendo el nuevo campo titular
        cout << "[" << nodo->dato.getBoletaTrabajador() << "] "
             << nodo->dato.getNombreCompleto()
             << " | Titular: " << nodo->dato.getIdGrupoTitular() << endl;
        listarRec(nodo->der);
    }
}

// --- PERSISTENCIA JSON ---

void ArbolProfesores::guardarEnArchivo() {
    ofstream archivo("data/profesores.json");
    if (!archivo.is_open()) return;

    archivo << "[\n";
    bool primero = true;
    guardarRec(raiz, archivo, primero);
    archivo << "\n]";
    archivo.close();
}

void ArbolProfesores::guardarRec(NodoProfesor* nodo, ofstream& archivo, bool& primero) {
    if (nodo) {
        // Recorrido Pre-Order para guardar, aunque In-Order también sirve

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

        primero = false; // Ya pasamos el primero, los siguientes llevan coma

        guardarRec(nodo->izq, archivo, primero);
        guardarRec(nodo->der, archivo, primero);
    }
}

// Helper simple para limpiar comillas y comas del valor
string ArbolProfesores::extraerValorJson(string linea) {
    size_t posDosPuntos = linea.find(':');
    if (posDosPuntos == string::npos) return "";

    string valor = linea.substr(posDosPuntos + 1);

    // Buscar la primera comilla
    size_t firstQuote = valor.find('\"');
    // Buscar la última comilla
    size_t lastQuote = valor.rfind('\"');

    if (firstQuote != string::npos && lastQuote != string::npos && lastQuote > firstQuote) {
        return valor.substr(firstQuote + 1, lastQuote - firstQuote - 1);
    }
    return "";
}

void ArbolProfesores::cargarDeArchivo() {
    ifstream archivo("data/profesores.json");
    if (!archivo.is_open()) return;

    string linea;
    Profesor pActual;
    bool leyendoObjeto = false;

    // Lectura lineal simple buscando claves
    while (getline(archivo, linea)) {
        if (linea.find("{") != string::npos) {
            leyendoObjeto = true;
            pActual = Profesor(); // Reiniciar objeto
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