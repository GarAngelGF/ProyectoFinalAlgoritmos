#ifndef PROYECTOFINALALGORITMOS_ESTRUCTCICLOS_H
#define PROYECTOFINALALGORITMOS_ESTRUCTCICLOS_H

#include "../Modelos/Ciclo.h"
#include <fstream>
#include <iostream>
#include <sstream>

struct NodoCiclo {
    Ciclo dato;
    NodoCiclo* siguiente;
    NodoCiclo(Ciclo c) : dato(c), siguiente(nullptr) {}
};

class ListaCiclos {
private:
    NodoCiclo* cabeza;

public:
    ListaCiclos();
    ~ListaCiclos();

    void insertar(Ciclo c);
    string obtenerCicloActual(); // Devuelve el nombre del primer ciclo activo
    void listar();

    void guardarEnArchivo();
    void cargarDeArchivo();
};

#endif //PROYECTOFINALALGORITMOS_ESTRUCTCICLOS_H