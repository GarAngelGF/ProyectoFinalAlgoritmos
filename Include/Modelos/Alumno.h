#ifndef PROYECTOFINALALGORITMOS_ALUMNO_H
#define PROYECTOFINALALGORITMOS_ALUMNO_H

#include <string>
#include "../Utilidades/Comunes.h" // Importante: para Fecha, Direccion, Tutor

using namespace std;

class Alumno {
private:
    string boleta;
    string nombreCompleto;
    Fecha nacimiento;
    string curp;
    char genero; // 'M' o 'F'
    Direccion direccion;
    Tutor tutor;

    // Relaciones lógicas (IDs, no punteros)
    string idGrupoInscrito;
    string nombreCiclo;
    bool estatusInscrito; // true = Activo, false = Baja

public:
    // Constructor
    Alumno();

    // Getters (Lectura)
    string getBoleta() const;
    string getNombreCompleto() const;
    Fecha getNacimiento() const;
    string getCurp() const;
    char getGenero() const;
    Direccion getDireccion() const;
    Tutor getTutor() const;
    string getIdGrupoInscrito() const;
    string getNombreCiclo() const;
    bool getEstatusInscrito() const;

    // Setters (Escritura)
    void setBoleta(const string& b);
    void setNombreCompleto(const string& n);
    void setNacimiento(Fecha f);
    void setCurp(const string& c);
    void setGenero(char g);
    void setDireccion(Direccion d);
    void setTutor(Tutor t);
    void setIdGrupoInscrito(const string& id);
    void setNombreCiclo(const string& ciclo);
    void setEstatusInscrito(bool estado);
};
#endif //PROYECTOFINALALGORITMOS_ALUMNO_H