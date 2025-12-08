#ifndef PROYECTOFINALALGORITMOS_GRUPO_H
#define PROYECTOFINALALGORITMOS_GRUPO_H

#include <string>
using namespace std;

class Grupo {
private:
    string idGrupo; // "1MF"
    int nivel;      // 1
    char turno;     // 'M'
    char secuencia; // 'F'

public:
    Grupo();
    Grupo(string id, int n, char t, char s); // Constructor sobrecargado útil

    string getIdGrupo() const;
    int getNivel() const;
    char getTurno() const;
    char getSecuencia() const;

    void setIdGrupo(const string& id);
    void setNivel(int n);
    void setTurno(char t);
    void setSecuencia(char s);
};

#endif //PROYECTOFINALALGORITMOS_GRUPO_H