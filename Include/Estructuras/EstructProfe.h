#ifndef PROYECTOFINALALGORITMOS_ESTRUCTPROFE_H
#define PROYECTOFINALALGORITMOS_ESTRUCTPROFE_H

#include "../Modelos/Profesor.h"
#include <fstream>
#include <iostream>
#include <sstream>

struct NodoProfesor {
    Profesor dato;
    NodoProfesor* siguiente;
    NodoProfesor(Profesor p) : dato(p), siguiente(nullptr) {}
};

class ListaProfesores {
private:
    NodoProfesor* cabeza;

public:
    ListaProfesores();
    ~ListaProfesores();

    void insertarInicio(Profesor p);
    void listar();
    Profesor* buscar(string cedula);

    void guardarEnArchivo();
    void cargarDeArchivo();
};

#endif //PROYECTOFINALALGORITMOS_ESTRUCTPROFE_H