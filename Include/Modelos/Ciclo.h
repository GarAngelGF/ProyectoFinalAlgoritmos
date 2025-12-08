#ifndef PROYECTOFINALALGORITMOS_CICLO_H
#define PROYECTOFINALALGORITMOS_CICLO_H

#include <string>
#include "../Utilidades/Comunes.h"

using namespace std;

class Ciclo {
private:
    string nombreCiclo; // "2024-2025"
    Fecha inicio;
    Fecha fin;
    bool activo;

public:
    Ciclo();

    string getNombreCiclo() const;
    Fecha getInicio() const;
    Fecha getFin() const;
    bool isActivo() const; // Convención: getters booleanos suelen llamarse is...

    void setNombreCiclo(const string& n);
    void setInicio(Fecha i);
    void setFin(Fecha f);
    void setActivo(bool a);
};

#endif