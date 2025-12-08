#ifndef PROYECTOFINALALGORITMOS_PROFESOR_H
#define PROYECTOFINALALGORITMOS_PROFESOR_H

#include <string>
#include "../Utilidades/Comunes.h"

using namespace std;

class Profesor {
private:
    string boletaTrabajador;
    string nombreCompleto;
    string cedula;
    string telefono;
    string email;
    Direccion direccion;
    string gruposAsignados; // IDs separados por coma o pipe

public:
    Profesor();

    string getBoletaTrabajador() const;
    string getNombreCompleto() const;
    string getCedula() const;
    string getTelefono() const;
    string getEmail() const;
    Direccion getDireccion() const;
    string getGruposAsignados() const;

    void setBoletaTrabajador(const string& b);
    void setNombreCompleto(const string& n);
    void setCedula(const string& c);
    void setTelefono(const string& t);
    void setEmail(const string& e);
    void setDireccion(Direccion d);
    void setGruposAsignados(const string& g);

    // Método extra útil para negocio
    void agregarGrupo(string idGrupo);
};
#endif //PROYECTOFINALALGORITMOS_PROFESOR_H