#include "../../include/Modelos/Ciclo.h"

Ciclo::Ciclo() {
    nombreCiclo = "";
    inicio = {0,0,0};
    fin = {0,0,0};
    activo = false;
}

// Getters
string Ciclo::getNombreCiclo() const { return nombreCiclo; }
Fecha Ciclo::getInicio() const { return inicio; }
Fecha Ciclo::getFin() const { return fin; }
bool Ciclo::isActivo() const { return activo; }

// Setters
void Ciclo::setNombreCiclo(const string& n) { nombreCiclo = n; }
void Ciclo::setInicio(Fecha i) { inicio = i; }
void Ciclo::setFin(Fecha f) { fin = f; }
void Ciclo::setActivo(bool a) { activo = a; }