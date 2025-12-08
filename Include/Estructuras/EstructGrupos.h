#ifndef PROYECTOFINALALGORITMOS_ESTRUCTGRUPOS_H
#define PROYECTOFINALALGORITMOS_ESTRUCTGRUPOS_H

#include "../Modelos/Grupo.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Nodo para lista circular
struct NodoGrupo {
    Grupo dato;
    NodoGrupo* siguiente;
    NodoGrupo(Grupo g) : dato(g), siguiente(nullptr) {}
};

class ListaGrupos {
private:
    NodoGrupo* cabeza;

    // Metodo privado auxiliar para leer JSON
    string extraerValorJson(string linea);

public:
    ListaGrupos();
    ~ListaGrupos();

    void insertar(Grupo grupo); // Mantiene la circularidad
    bool existe(string id);
    void listar();

    NodoGrupo* getCabeza() const { return cabeza; }

    // Persistencia JSON
    void guardarEnArchivo();
    void cargarDeArchivo();
};

#endif //PROYECTOFINALALGORITMOS_ESTRUCTGRUPOS_H