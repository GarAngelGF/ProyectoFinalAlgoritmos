#ifndef PROYECTOFINALALGORITMOS_ESTRUCTPROFE_H
#define PROYECTOFINALALGORITMOS_ESTRUCTPROFE_H

#include "../Modelos/Profesor.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Estructura del nodo para Árbol Binario
struct NodoProfesor {
    Profesor dato;
    NodoProfesor* izq;
    NodoProfesor* der;

    NodoProfesor(Profesor p) : dato(p), izq(nullptr), der(nullptr) {}
};

class ArbolProfesores {
private:
    NodoProfesor* raiz;

    // Métodos auxiliares recursivos (privados)
    void insertarRec(NodoProfesor*& nodo, Profesor p);
    void listarRec(NodoProfesor* nodo);
    void destruirRec(NodoProfesor* nodo);
    void guardarRec(NodoProfesor* nodo, ofstream& archivo, bool& primero);

    // Auxiliar para lectura de JSON manual
    string extraerValorJson(string linea);

public:
    ArbolProfesores();
    ~ArbolProfesores();

    void insertar(Profesor p);
    void listar();
    Profesor* buscar(string boleta); // Búsqueda binaria optimizada

    // Persistencia en JSON
    void guardarEnArchivo();
    void cargarDeArchivo();
};

#endif //PROYECTOFINALALGORITMOS_ESTRUCTPROFE_H