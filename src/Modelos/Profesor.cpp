#include "../../include/Modelos/Profesor.h"

Profesor::Profesor() {
    boletaTrabajador = "";
    nombreCompleto = "";
    telefono = "";
    gruposAsignados = "";
    idGrupoTitular = "SIN_ASIGNAR"; // Inicialización por defecto
}

// --- Getters ---
string Profesor::getBoletaTrabajador() const { return boletaTrabajador; }
string Profesor::getNombreCompleto() const { return nombreCompleto; }
string Profesor::getTelefono() const { return telefono; }
Direccion Profesor::getDireccion() const { return direccion; }
string Profesor::getIdGrupoTitular() const { return idGrupoTitular; }
string Profesor::getGruposAsignados() const { return gruposAsignados; }

// --- Setters ---
void Profesor::setBoletaTrabajador(const string& b) { boletaTrabajador = b; }
void Profesor::setNombreCompleto(const string& n) { nombreCompleto = n; }
void Profesor::setTelefono(const string& t) { telefono = t; }
void Profesor::setDireccion(Direccion d) { direccion = d; }
void Profesor::setIdGrupoTitular(const string& id) { idGrupoTitular = id; }
void Profesor::setGruposAsignados(const string& g) { gruposAsignados = g; }

// --- Métodos Extra ---
void Profesor::agregarGrupo(string idGrupo) {
    if (gruposAsignados.empty()) {
        gruposAsignados = idGrupo;
    } else {
        gruposAsignados += "," + idGrupo;
    }
}