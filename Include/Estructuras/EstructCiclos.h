#ifndef PROYECTOFINALALGORITMOS_ESTRUCTCICLOS_H
#define PROYECTOFINALALGORITMOS_ESTRUCTCICLOS_H

#include "../Modelos/Ciclo.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Nodo para Lista Simple
struct NodoCiclo {
    Ciclo dato;
    NodoCiclo* siguiente;
    NodoCiclo(Ciclo c) : dato(c), siguiente(nullptr) {}
};

class ListaCiclos {
private:
    NodoCiclo* cabeza;

    // Metodo auxiliar para lectura manual de JSON
    string extraerValorJson(string linea);

public:
    ListaCiclos();
    ~ListaCiclos();

    void insertar(Ciclo c);      // Inserta al inicio (LIFO) o final, según preferencia (aquí usamos inicio por simplicidad)
    string obtenerCicloActual(); // Devuelve el nombre del primer ciclo activo
    void listar();

    // Persistencia JSON
    void guardarEnArchivo();
    void cargarDeArchivo();
};

#endif //PROYECTOFINALALGORITMOS_ESTRUCTCICLOS_H