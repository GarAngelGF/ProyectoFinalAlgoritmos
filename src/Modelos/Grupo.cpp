#include "../../include/Modelos/Grupo.h"

Grupo::Grupo() {
    idGrupo = "";
    nivel = 0;
    turno = ' ';
    secuencia = ' ';
}

Grupo::Grupo(string id, int n, char t, char s) {
    idGrupo = id;
    nivel = n;
    turno = t;
    secuencia = s;
}

// Getters
string Grupo::getIdGrupo() const { return idGrupo; }
int Grupo::getNivel() const { return nivel; }
char Grupo::getTurno() const { return turno; }
char Grupo::getSecuencia() const { return secuencia; }

// Setters
void Grupo::setIdGrupo(const string& id) { idGrupo = id; }
void Grupo::setNivel(int n) { nivel = n; }
void Grupo::setTurno(char t) { turno = t; }
void Grupo::setSecuencia(char s) { secuencia = s; }