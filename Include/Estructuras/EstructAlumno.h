#ifndef PROYECTOFINALALGORITMOS_ESTRUCTALUMNO_H
#define PROYECTOFINALALGORITMOS_ESTRUCTALUMNO_H


#include "../Modelos/Alumno.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// Nodo específico para la LISTA DOBLE
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

    // Metodo auxiliar para parseo manual de JSON
    string extraerValorJson(string linea);

public:
    ListaAlumnos();
    ~ListaAlumnos();

    void insertar(Alumno alumno); // Inserta al final (cola)
    void eliminar(string boleta);
    Alumno* buscar(string boleta); // Búsqueda lineal
    void listar(bool soloActivos);

    // Persistencia en JSON
    void guardarEnArchivo();
    void cargarDeArchivo();
};

#endif //PROYECTOFINALALGORITMOS_ESTRUCTALUMNO_H