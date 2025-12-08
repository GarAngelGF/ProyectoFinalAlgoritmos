#include <iostream>
#include "Include/Controladores/GestionEscolar.h"


using namespace std;

int main() {
    cout << "Proyecto final de Algoritmos Compuracionales" << "Equipo 6: " << endl;
    // 1. Instanciamos el controlador principal
    GestionEscolar sistema;

    // 2. Cargamos los datos desde los archivos (o creamos defaults)
    //    Esto prepara las listas en memoria antes de mostrar nada al usuario.
    sistema.inicializarSistema();

    // 3. Lanzamos el bucle del menú principal
    //    El programa se quedará aquí dentro hasta que el usuario elija "Salir"
    sistema.menuPrincipal();

    // 4. Salida limpia
    cout << ">> Ejecucion finalizada correctamente." << endl;
    return 0;
}
