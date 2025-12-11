#include "../../include/Estructuras/EstructGrupos.h"
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

ListaGrupos::ListaGrupos() : cabeza(nullptr) {}

ListaGrupos::~ListaGrupos() {
    if (!cabeza) return;
    NodoGrupo* actual = cabeza;
    NodoGrupo* ultimo = cabeza;
    while (ultimo->siguiente != cabeza) {
        ultimo = ultimo->siguiente;
    }
    ultimo->siguiente = nullptr;

    while (actual != nullptr) {
        NodoGrupo* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

void ListaGrupos::insertar(Grupo grupo) {
    NodoGrupo* nuevo = new NodoGrupo(grupo);
    if (!cabeza) {
        cabeza = nuevo;
        nuevo->siguiente = cabeza;
    }
    else {
        NodoGrupo* temp = cabeza;
        while (temp->siguiente != cabeza) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
        nuevo->siguiente = cabeza;
    }
}

bool ListaGrupos::existe(string id) {
    if (!cabeza) return false;
    NodoGrupo* temp = cabeza;
    do {
        if (temp->dato.getIdGrupo() == id) return true;
        temp = temp->siguiente;
    } while (temp != cabeza);
    return false;
}

void ListaGrupos::listar() {
    if (!cabeza) { cout << "No hay grupos registrados." << endl; return; }
    NodoGrupo* temp = cabeza;
    cout << "--- LISTA DE GRUPOS (Circular) ---" << endl;
    do {
        cout << "ID: " << temp->dato.getIdGrupo()
            << " | Nivel: " << temp->dato.getNivel()
            << " | Turno: " << temp->dato.getTurno()
            << " | Sec: " << temp->dato.getSecuencia() << endl;
        temp = temp->siguiente;
    } while (temp != cabeza);
}

// --- PERSISTENCIA JSON ---

void ListaGrupos::guardarEnArchivo() {
#ifdef _WIN32
    _mkdir("Data");
#else
    mkdir("Data", 0777);
#endif

    ofstream archivo("Data/grupos.json");
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo crear el archivo Data/grupos.json" << endl;
        return;
    }

    if (!cabeza) {
        archivo << "[]";
        archivo.close();
        return;
    }

    archivo << "[\n";
    NodoGrupo* temp = cabeza;
    do {
        archivo << "  {\n";
        archivo << "    \"id\": \"" << temp->dato.getIdGrupo() << "\",\n";
        archivo << "    \"nivel\": \"" << temp->dato.getNivel() << "\",\n";
        archivo << "    \"turno\": \"" << temp->dato.getTurno() << "\",\n";
        archivo << "    \"secuencia\": \"" << temp->dato.getSecuencia() << "\"\n";
        archivo << "  }";

        if (temp->siguiente != cabeza) {
            archivo << ",";
        }
        archivo << "\n";

        temp = temp->siguiente;
    } while (temp != cabeza);

    archivo << "]";
    archivo.close();
}

string ListaGrupos::extraerValorJson(string linea) {
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

void ListaGrupos::cargarDeArchivo() {
    ifstream archivo("Data/grupos.json"); // Ruta actualizada
    if (!archivo.is_open()) return;

    string linea;
    Grupo gActual;
    bool leyendoObjeto = false;

    while (getline(archivo, linea)) {
        if (linea.find("{") != string::npos) {
            leyendoObjeto = true;
            gActual = Grupo();
        }
        else if (linea.find("}") != string::npos && leyendoObjeto) {
            insertar(gActual);
            leyendoObjeto = false;
        }
        else if (leyendoObjeto) {
            if (linea.find("\"id\"") != string::npos)
                gActual.setIdGrupo(extraerValorJson(linea));
            else if (linea.find("\"nivel\"") != string::npos) {
                string val = extraerValorJson(linea);
                if (!val.empty()) gActual.setNivel(stoi(val));
            }
            else if (linea.find("\"turno\"") != string::npos) {
                string val = extraerValorJson(linea);
                if (!val.empty()) gActual.setTurno(val[0]);
            }
            else if (linea.find("\"secuencia\"") != string::npos) {
                string val = extraerValorJson(linea);
                if (!val.empty()) gActual.setSecuencia(val[0]);
            }
        }
    }
    archivo.close();
}