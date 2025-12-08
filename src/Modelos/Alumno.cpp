#include "../../include/Modelos/Alumno.h"

// Constructor: Inicializa valores por defecto para evitar basura
Alumno::Alumno() {
    boleta = "";
    nombreCompleto = "";
    curp = "";
    genero = ' ';
    idGrupoInscrito = "SIN_ASIGNAR";
    nombreCiclo = "";
    estatusInscrito = false;
    // Las structs (Fecha, Direccion) se inicializan con sus propios valores por defecto si los tienen, o basura si no.
    // Es buena práctica inicializar la fecha en 0
    nacimiento = {0, 0, 0}; 
}

// --- Implementación de Getters ---
string Alumno::getBoleta() const { return boleta; }
string Alumno::getNombreCompleto() const { return nombreCompleto; }
Fecha Alumno::getNacimiento() const { return nacimiento; }
string Alumno::getCurp() const { return curp; }
char Alumno::getGenero() const { return genero; }
Direccion Alumno::getDireccion() const { return direccion; }
Tutor Alumno::getTutor() const { return tutor; }
string Alumno::getIdGrupoInscrito() const { return idGrupoInscrito; }
string Alumno::getNombreCiclo() const { return nombreCiclo; }
bool Alumno::getEstatusInscrito() const { return estatusInscrito; }

// --- Implementación de Setters ---
void Alumno::setBoleta(const string& b) { boleta = b; }
void Alumno::setNombreCompleto(const string& n) { nombreCompleto = n; }
void Alumno::setNacimiento(Fecha f) { nacimiento = f; }
void Alumno::setCurp(const string& c) { curp = c; }
void Alumno::setGenero(char g) { genero = g; }
void Alumno::setDireccion(Direccion d) { direccion = d; }
void Alumno::setTutor(Tutor t) { tutor = t; }
void Alumno::setIdGrupoInscrito(const string& id) { idGrupoInscrito = id; }
void Alumno::setNombreCiclo(const string& ciclo) { nombreCiclo = ciclo; }
void Alumno::setEstatusInscrito(bool estado) { estatusInscrito = estado; }