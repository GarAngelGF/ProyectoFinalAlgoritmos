#include "../../include/Estructuras/EstructAlumno.h"

ListaAlumnos::ListaAlumnos() : cabeza(nullptr), cola(nullptr) {}

ListaAlumnos::~ListaAlumnos() {
    NodoAlumno* actual = cabeza;
    while (actual != nullptr) {
        NodoAlumno* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

void ListaAlumnos::insertar(Alumno alumno) {
    NodoAlumno* nuevo = new NodoAlumno(alumno);
    if (!cabeza) {
        cabeza = cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    }
}

void ListaAlumnos::eliminar(string boleta) {
    if (!cabeza) return;

    NodoAlumno* actual = cabeza;
    while (actual != nullptr) {
        if (actual->dato.getBoleta() == boleta) {
            // Caso 1: Es la cabeza
            if (actual == cabeza) {
                cabeza = actual->siguiente;
                if (cabeza) cabeza->anterior = nullptr;
                else cola = nullptr; // Si la lista quedó vacía
            }
            // Caso 2: Es la cola
            else if (actual == cola) {
                cola = actual->anterior;
                cola->siguiente = nullptr;
            }
            // Caso 3: Intermedio
            else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
            }
            delete actual;
            cout << ">> Alumno eliminado." << endl;
            return;
        }
        actual = actual->siguiente;
    }
    cout << ">> Alumno no encontrado." << endl;
}

Alumno* ListaAlumnos::buscar(string boleta) {
    NodoAlumno* temp = cabeza;
    while (temp) {
        if (temp->dato.getBoleta() == boleta) return &temp->dato;
        temp = temp->siguiente;
    }
    return nullptr;
}

void ListaAlumnos::listar(bool soloActivos) {
    NodoAlumno* temp = cabeza;
    cout << "--- LISTA ALUMNOS ---" << endl;
    while (temp) {
        if (!soloActivos || temp->dato.getEstatusInscrito()) {
            cout << temp->dato.getBoleta() << " - " << temp->dato.getNombreCompleto() 
                 << " [" << (temp->dato.getEstatusInscrito() ? "ACTIVO" : "BAJA") << "]" << endl;
        }
        temp = temp->siguiente;
    }
}

void ListaAlumnos::guardarEnArchivo() {
    ofstream archivo("data/alumnos.txt");
    NodoAlumno* temp = cabeza;
    while (temp) {
        // Serialización simple separada por '|'
        archivo << temp->dato.getBoleta() << "|"
                << temp->dato.getNombreCompleto() << "|"
                << temp->dato.getIdGrupoInscrito() << "|"
                << (temp->dato.getEstatusInscrito() ? "1" : "0") << endl;
        // Nota: En un sistema real, guardarías TODOS los campos (fecha, direccion, etc.)
        temp = temp->siguiente;
    }
    archivo.close();
}

void ListaAlumnos::cargarDeArchivo() {
    ifstream archivo("data/alumnos.txt");
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string segmento;
        Alumno a;
        
        string boleta, nombre, grupo, estadoStr;
        
        getline(ss, boleta, '|'); a.setBoleta(boleta);
        getline(ss, nombre, '|'); a.setNombreCompleto(nombre);
        getline(ss, grupo, '|');  a.setIdGrupoInscrito(grupo);
        getline(ss, estadoStr, '|'); a.setEstatusInscrito(estadoStr == "1");

        insertar(a);
    }
    archivo.close();
}