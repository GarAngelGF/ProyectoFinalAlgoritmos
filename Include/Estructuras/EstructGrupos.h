#ifndef PROYECTOFINALALGORITMOS_ESTRUCTGRUPOS_H
#define PROYECTOFINALALGORITMOS_ESTRUCTGRUPOS_H

#include "../Modelos/Grupo.h"
#include <fstream>
#include <iostream>
#include <sstream>

struct NodoGrupo {
    Grupo dato;
    NodoGrupo* siguiente;
    NodoGrupo(Grupo g) : dato(g), siguiente(nullptr) {}
};

class ListaGrupos {
private:
    NodoGrupo* cabeza;

public:
    ListaGrupos();
    ~ListaGrupos();

    void insertar(Grupo grupo); // Inserta al final manteniendo circularidad
    bool existe(string id);
    void listar();

    // El getter de cabeza es útil para recorrer externamente si fuera necesario
    NodoGrupo* getCabeza() const { return cabeza; }

    void guardarEnArchivo();
    void cargarDeArchivo();
};

#endif //PROYECTOFINALALGORITMOS_ESTRUCTGRUPOS_H