#include "../../include/Estructuras/EstructProfe.h"

ListaProfesores::ListaProfesores() : cabeza(nullptr) {}

ListaProfesores::~ListaProfesores() {
    while (cabeza) {
        NodoProfesor* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void ListaProfesores::insertarInicio(Profesor p) {
    NodoProfesor* nuevo = new NodoProfesor(p);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

void ListaProfesores::listar() {
    NodoProfesor* temp = cabeza;
    cout << "--- LISTA PROFESORES ---" << endl;
    while (temp) {
        cout << temp->dato.getBoletaTrabajador() << " - " << temp->dato.getNombreCompleto() << endl;
        temp = temp->siguiente;
    }
}

Profesor* ListaProfesores::buscar(string cedula) {
    NodoProfesor* temp = cabeza;
    while(temp) {
        if(temp->dato.getCedula() == cedula) return &temp->dato;
        temp = temp->siguiente;
    }
    return nullptr;
}

void ListaProfesores::guardarEnArchivo() {
    ofstream archivo("data/profesores.txt");
    NodoProfesor* temp = cabeza;
    while (temp) {
        archivo << temp->dato.getBoletaTrabajador() << "|"
                << temp->dato.getNombreCompleto() << "|"
                << temp->dato.getCedula() << endl;
        temp = temp->siguiente;
    }
    archivo.close();
}

void ListaProfesores::cargarDeArchivo() {
    ifstream archivo("data/profesores.txt");
    if (!archivo.is_open()) return;
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string bol, nom, ced;
        getline(ss, bol, '|');
        getline(ss, nom, '|');
        getline(ss, ced, '|');
        
        Profesor p;
        p.setBoletaTrabajador(bol);
        p.setNombreCompleto(nom);
        p.setCedula(ced);
        insertarInicio(p);
    }
    archivo.close();
}