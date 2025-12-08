#ifndef PROYECTOFINALALGORITMOS_VALIDACIONES_H
#define PROYECTOFINALALGORITMOS_VALIDACIONES_H

#include <string>
#include <iostream>
#include <limits> // Para numeric_limits
#include "Comunes.h" // Necesitamos conocer struct Fecha

using namespace std;

namespace Validaciones {

    // --- Validaciones Lógicas (Retornan true/false) ---

    // Verifica si un string contiene solo números
    bool esNumero(const string& s);

    // Verifica si una fecha es real (considera bisiestos)
    bool esFechaValida(const Fecha& f);

    // Verifica si un correo tiene formato básico (@ y .)
    bool esCorreoValido(const string& email);

    // --- Helpers de Captura (Piden datos hasta que sean válidos) ---

    // Pide un entero entre un rango (ej. para menús: 1 al 5)
    int pedirEntero(string mensaje, int min, int max);

    // Pide un string que no esté vacío
    string pedirCadena(string mensaje);

    // Pide una fecha válida y no deja avanzar hasta que sea correcta
    Fecha pedirFecha(string mensaje);

    // Limpia el buffer de entrada (útil después de un cin >>)
    void limpiarBuffer();
}
#endif //PROYECTOFINALALGORITMOS_VALIDACIONES_H