#include "../../include/Modelos/Profesor.h"

Profesor::Profesor() {
    boletaTrabajador = "";
    nombreCompleto = "";
    cedula = "";
    gruposAsignados = "";
}

// Getters
string Profesor::getBoletaTrabajador() const { return boletaTrabajador; }
string Profesor::getNombreCompleto() const { return nombreCompleto; }
string Profesor::getCedula() const { return cedula; }
string Profesor::getTelefono() const { return telefono; }
string Profesor::getEmail() const { return email; }
Direccion Profesor::getDireccion() const { return direccion; }
string Profesor::getGruposAsignados() const { return gruposAsignados; }

// Setters
void Profesor::setBoletaTrabajador(const string& b) { boletaTrabajador = b; }
void Profesor::setNombreCompleto(const string& n) { nombreCompleto = n; }
void Profesor::setCedula(const string& c) { cedula = c; }
void Profesor::setTelefono(const string& t) { telefono = t; }
void Profesor::setEmail(const string& e) { email = e; }
void Profesor::setDireccion(Direccion d) { direccion = d; }
void Profesor::setGruposAsignados(const string& g) { gruposAsignados = g; }

// Metodo extra: concatena grupos
void Profesor::agregarGrupo(string idGrupo) {
    if (gruposAsignados.empty()) {
        gruposAsignados = idGrupo;
    } else {
        gruposAsignados += "," + idGrupo;
    }
}