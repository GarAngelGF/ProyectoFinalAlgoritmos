#ifndef PROYECTOFINALALGORITMOS_PROFESOR_H
#define PROYECTOFINALALGORITMOS_PROFESOR_H

#include <string>
#include "../Utilidades/Comunes.h"

using namespace std;

class Profesor {
private:
    string boletaTrabajador;
    string nombreCompleto;
    string telefono;
    Direccion direccion;

    // Nuevo atributo para la vinculación solicitada
    string idGrupoTitular;

    // Se mantiene por si el profesor da clases en varios grupos además de ser titular
    string gruposAsignados;

public:
    Profesor();

    // Getters
    string getBoletaTrabajador() const;
    string getNombreCompleto() const;
    string getTelefono() const;
    Direccion getDireccion() const;
    string getIdGrupoTitular() const; // Nuevo Getter
    string getGruposAsignados() const;

    // Setters
    void setBoletaTrabajador(const string& b);
    void setNombreCompleto(const string& n);
    void setTelefono(const string& t);
    void setDireccion(Direccion d);
    void setIdGrupoTitular(const string& id); // Nuevo Setter
    void setGruposAsignados(const string& g);

    // Meetodo extra utilitario
    void agregarGrupo(string idGrupo);
};

#endif //PROYECTOFINALALGORITMOS_PROFESOR_H