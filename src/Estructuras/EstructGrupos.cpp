#include "../../include/Estructuras/EstructGrupos.h"

ListaGrupos::ListaGrupos() : cabeza(nullptr) {}

ListaGrupos::~ListaGrupos() {
    if (!cabeza) return;
    NodoGrupo* actual = cabeza;
    do {
        NodoGrupo* temp = actual;
        actual = actual->siguiente;
        delete temp;
    } while (actual != cabeza);
    // Nota: en implementaciones complejas hay que romper el ciclo antes de borrar
    // pero para este destructor simple funciona si se maneja con cuidado.
}

void ListaGrupos::insertar(Grupo grupo) {
    NodoGrupo* nuevo = new NodoGrupo(grupo);
    if (!cabeza) {
        cabeza = nuevo;
        nuevo->siguiente = cabeza; // Se apunta a sí mismo
    } else {
        NodoGrupo* temp = cabeza;
        while (temp->siguiente != cabeza) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
        nuevo->siguiente = cabeza; // Cierra el círculo
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
    if (!cabeza) { cout << "No hay grupos." << endl; return; }
    NodoGrupo* temp = cabeza;
    cout << "--- LISTA GRUPOS (Circular) ---" << endl;
    do {
        cout << "Grupo: " << temp->dato.getIdGrupo() << endl;
        temp = temp->siguiente;
    } while (temp != cabeza);
}

void ListaGrupos::guardarEnArchivo() {
    if (!cabeza) return;
    ofstream archivo("data/grupos.txt");
    NodoGrupo* temp = cabeza;
    do {
        archivo << temp->dato.getIdGrupo() << "|"
                << temp->dato.getNivel() << "|"
                << temp->dato.getTurno() << "|"
                << temp->dato.getSecuencia() << endl;
        temp = temp->siguiente;
    } while (temp != cabeza);
    archivo.close();
}

void ListaGrupos::cargarDeArchivo() {
    ifstream archivo("data/grupos.txt");
    if (!archivo.is_open()) return;
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, n_str, t_str, s_str;
        
        getline(ss, id, '|');
        getline(ss, n_str, '|');
        getline(ss, t_str, '|');
        getline(ss, s_str, '|');
        
        if(!id.empty()) {
            Grupo g(id, stoi(n_str), t_str[0], s_str[0]);
            insertar(g);
        }
    }
    archivo.close();
}