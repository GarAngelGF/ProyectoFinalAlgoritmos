#include "../../include/Estructuras/EstructCiclos.h"

ListaCiclos::ListaCiclos() : cabeza(nullptr) {}

ListaCiclos::~ListaCiclos() {
    while (cabeza) {
        NodoCiclo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void ListaCiclos::insertar(Ciclo c) {
    NodoCiclo* nuevo = new NodoCiclo(c);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

string ListaCiclos::obtenerCicloActual() {
    NodoCiclo* temp = cabeza;
    while(temp) {
        if(temp->dato.isActivo()) return temp->dato.getNombreCiclo();
        temp = temp->siguiente;
    }
    return "SIN_CICLO";
}

void ListaCiclos::listar() {
    NodoCiclo* temp = cabeza;
    cout << "--- CICLOS ---" << endl;
    while(temp) {
        cout << temp->dato.getNombreCiclo() << " [" << (temp->dato.isActivo()?"ACTIVO":"CERRADO") << "]" << endl;
        temp = temp->siguiente;
    }
}

void ListaCiclos::guardarEnArchivo() {
    ofstream archivo("data/ciclos.txt");
    NodoCiclo* temp = cabeza;
    while (temp) {
        archivo << temp->dato.getNombreCiclo() << "|"
                << (temp->dato.isActivo() ? "1" : "0") << endl;
        temp = temp->siguiente;
    }
    archivo.close();
}

void ListaCiclos::cargarDeArchivo() {
    ifstream archivo("data/ciclos.txt");
    if (!archivo.is_open()) return;
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nom, actStr;
        getline(ss, nom, '|');
        getline(ss, actStr, '|');

        Ciclo c;
        c.setNombreCiclo(nom);
        c.setActivo(actStr == "1");
        // Nota: Fechas simplificadas o ignoradas en este ejemplo de carga
        insertar(c);
    }
    archivo.close();
}