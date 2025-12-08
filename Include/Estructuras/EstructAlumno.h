#ifndef PROYECTOFINALALGORITMOS_ESTRUCTALUMNO_H
#define PROYECTOFINALALGORITMOS_ESTRUCTALUMNO_H

#include "../Modelos/Alumno.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Nodo específico para la lista doble
struct NodoAlumno {
    Alumno dato;
    NodoAlumno* siguiente;
    NodoAlumno* anterior;

    NodoAlumno(Alumno a) : dato(a), siguiente(nullptr), anterior(nullptr) {}
};

class ListaAlumnos {
private:
    NodoAlumno* cabeza;
    NodoAlumno* cola; // Puntero al final para insertar rápido

public:
    ListaAlumnos();
    ~ListaAlumnos(); // Destructor vital

    void insertar(Alumno alumno);
    void eliminar(string boleta);
    Alumno* buscar(string boleta); // Retorna puntero al dato para modificarlo
    void listar(bool soloActivos);

    // Persistencia
    void guardarEnArchivo();
    void cargarDeArchivo();
};

#endif //PROYECTOFINALALGORITMOS_ESTRUCTALUMNO_H