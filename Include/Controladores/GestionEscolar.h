#ifndef PROYECTOFINALALGORITMOS_GESTIONESCOLAR_H
#define PROYECTOFINALALGORITMOS_GESTIONESCOLAR_H


#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// Incluimos las estructuras de datos que manejan la memoria
#include "../Estructuras/EstructAlumno.h"
#include "../Estructuras/EstructProfe.h"
#include "../Estructuras/EstructGrupos.h"
#include "../Estructuras/EstructCiclos.h"

// Incluimos validaciones para pedir datos limpios
#include "../Utilidades/Validaciones.h"

using namespace std;

class GestionEscolar {
private:
    // --- COMPOSICIÓN: El sistema "tiene" listas ---
    ListaAlumnos alumnos;
    ListaProfesores profesores;
    ListaGrupos grupos;
    ListaCiclos ciclos;

    // --- Métodos Privados de Utilidad ---
    string generarBoletaAlumno();      // Genera boleta (Año + Random)
    string generarBoletaProfesor();    // Genera ID (DOC + Random)
    void cargarDatosIniciales();       // Si no hay archivos, crea datos default

public:
    GestionEscolar();

    // Configuración inicial
    void inicializarSistema();

    // --- MENÚS DEL SISTEMA ---
    void menuPrincipal();

    void menuAlumnos();
    void menuProfesores();
    void menuGrupos();
    void menuCiclos();

    // --- Lógica de Negocio (Fachada) ---
    // Alumnos
    void registrarAlumno();
    void inscribirAlumno();
    void darBajaAlumno();
    void buscarAlumno();

    // Profesores
    void registrarProfesor();
    void buscarProfesor();

    // Grupos y Ciclos
    void crearGrupo();
    void crearCiclo();
};

#endif //PROYECTOFINALALGORITMOS_GESTIONESCOLAR_H