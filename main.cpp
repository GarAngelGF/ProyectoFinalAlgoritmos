#include <iostream>
#include "Include/Controladores/GestionEscolar.h"


using namespace std;

int main() {
    cout << "Proyecto final de Algoritmos Compuracionales" << "Equipo 6: " << endl;
    GestionEscolar sistema;
    sistema.inicializarSistema();
    sistema.menuPrincipal();
    cout << ">> Ejecucion finalizada correctamente." << endl;
    return 0;
}
