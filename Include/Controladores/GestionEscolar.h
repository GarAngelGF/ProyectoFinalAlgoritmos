#ifndef PROYECTOFINALALGORITMOS_GESTIONESCOLAR_H
#define PROYECTOFINALALGORITMOS_GESTIONESCOLAR_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// Incluimos las estructuras actualizadas
#include "../Estructuras/EstructAlumno.h"
#include "../Estructuras/EstructProfe.h"
#include "../Estructuras/EstructGrupos.h"
#include "../Estructuras/EstructCiclos.h"

#include "../Utilidades/Validaciones.h"

using namespace std;

class GestionEscolar {
private:
    // --- Estructuras de Datos ---
    ListaAlumnos alumnos;      // Lista Doble (JSON)
    ArbolProfesores profesores; // Árbol Binario (JSON)
    ListaGrupos grupos;        // Lista Circular (JSON)
    ListaCiclos ciclos;        // Lista Simple (JSON)

    // --- Métodos Privados de Utilidad ---
    string generarBoletaAlumno();
    string generarBoletaProfesor();
    void cargarDatosIniciales();

    void limpiarPantalla();
    void pausar();

public:
    GestionEscolar();

    // Configuración inicial
    void inicializarSistema();

    // --- MENÚS DEL SISTEMA ---
    void menuPrincipal();

    void menuAlumnos();
    void menuProfesores();
    void menuGrupos(); // Submenú con opción de ver registros
    void menuCiclos(); // Submenú con opción de ver registros

    // --- Lógica de Negocio ---

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

    // --- NUEVO: Reporte General ---
    void generarReporteGeneral();
};

#endif //PROYECTOFINALALGORITMOS_GESTIONESCOLAR_H