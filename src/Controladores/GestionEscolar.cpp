#include "../../include/Controladores/GestionEscolar.h"

// Constructor
GestionEscolar::GestionEscolar() {
    srand(time(0)); // Semilla para números aleatorios
}

void GestionEscolar::inicializarSistema() {
    cout << ">> Cargando sistema..." << endl;

    // Delegamos la carga a cada lista
    ciclos.cargarDeArchivo();
    grupos.cargarDeArchivo();
    profesores.cargarDeArchivo();
    alumnos.cargarDeArchivo();

    // Si no hay ciclos, creamos uno por defecto para que el sistema funcione
    if (ciclos.obtenerCicloActual() == "SIN_CICLO") {
        cargarDatosIniciales();
    }
}

void GestionEscolar::cargarDatosIniciales() {
    // Crea un ciclo default si es la primera vez que corre el programa
    Ciclo c;
    c.setNombreCiclo("2024-2025");
    c.setActivo(true);
    ciclos.insertar(c);
    ciclos.guardarEnArchivo();

    // Crea grupos base
    grupos.insertar(Grupo("1MA", 1, 'M', 'A'));
    grupos.insertar(Grupo("2VA", 2, 'V', 'A'));
    grupos.guardarEnArchivo();
}

// --- GENERADORES DE ID ---

string GestionEscolar::generarBoletaAlumno() {
    string ciclo = ciclos.obtenerCicloActual();
    string anio = (ciclo.length() >= 4) ? ciclo.substr(0, 4) : "2024";
    string randomPart = to_string(rand() % 900000 + 100000); // 6 dígitos
    return anio + randomPart;
}

string GestionEscolar::generarBoletaProfesor() {
    return "DOC-" + to_string(rand() % 90000 + 10000);
}

// --- MENÚ PRINCIPAL ---

void GestionEscolar::menuPrincipal() {
    int opc;
    do {
        // system("cls"); // Opcional: limpiar pantalla (windows)
        cout << "\n===============================" << endl;
        cout << "   SISTEMA DE CONTROL ESCOLAR" << endl;
        cout << "===============================" << endl;
        cout << "1. Gestion de Alumnos" << endl;
        cout << "2. Gestion de Profesores" << endl;
        cout << "3. Ver Grupos" << endl;
        cout << "4. Ver Ciclos Escolares" << endl;
        cout << "0. Salir" << endl;
        cout << "===============================" << endl;

        opc = Validaciones::pedirEntero("Seleccione una opcion: ", 0, 4);

        switch (opc) {
            case 1: menuAlumnos(); break;
            case 2: menuProfesores(); break;
            case 3:
                grupos.listar();
                Validaciones::pedirCadena("Presione Enter para continuar...");
                break;
            case 4:
                ciclos.listar();
                Validaciones::pedirCadena("Presione Enter para continuar...");
                break;
            case 0: cout << "Saliendo del sistema..." << endl; break;
        }
    } while (opc != 0);
}

// --- GESTIÓN DE ALUMNOS ---

void GestionEscolar::menuAlumnos() {
    int opc;
    do {
        cout << "\n--- MENU ALUMNOS ---" << endl;
        cout << "1. Registrar Nuevo Alumno" << endl;
        cout << "2. Inscribir Alumno a Grupo" << endl;
        cout << "3. Buscar Alumno" << endl;
        cout << "4. Dar de Baja (Eliminar)" << endl;
        cout << "5. Listar Todos" << endl;
        cout << "0. Regresar" << endl;

        opc = Validaciones::pedirEntero("Opcion: ", 0, 5);

        switch(opc) {
            case 1: registrarAlumno(); break;
            case 2: inscribirAlumno(); break;
            case 3: buscarAlumno(); break;
            case 4: darBajaAlumno(); break;
            case 5: alumnos.listar(false); break;
        }
    } while (opc != 0);
}

void GestionEscolar::registrarAlumno() {
    cout << "\n--- REGISTRO DE ALUMNO ---" << endl;
    Alumno nuevo;

    // 1. Usamos Validaciones para pedir datos seguros
    nuevo.setNombreCompleto(Validaciones::pedirCadena("Nombre Completo: "));
    nuevo.setCurp(Validaciones::pedirCadena("CURP: "));

    char genero;
    cout << "Genero (M/F): "; cin >> genero; Validaciones::limpiarBuffer();
    nuevo.setGenero(genero);

    nuevo.setNacimiento(Validaciones::pedirFecha("Fecha de Nacimiento"));

    // Datos del tutor
    Tutor t;
    t.nombre = Validaciones::pedirCadena("Nombre del Tutor: ");
    t.parentesco = Validaciones::pedirCadena("Parentesco: ");
    nuevo.setTutor(t);

    // 2. Generamos datos automáticos
    nuevo.setBoleta(generarBoletaAlumno());
    nuevo.setNombreCiclo(ciclos.obtenerCicloActual());
    nuevo.setIdGrupoInscrito("SIN_ASIGNAR");
    nuevo.setEstatusInscrito(false);

    // 3. Insertamos en la lista y guardamos
    alumnos.insertar(nuevo);
    alumnos.guardarEnArchivo();

    cout << ">> Alumno registrado con EXITO. Boleta asignada: " << nuevo.getBoleta() << endl;
}

void GestionEscolar::inscribirAlumno() {
    cout << "\n--- INSCRIPCION ---" << endl;
    string boleta = Validaciones::pedirCadena("Ingrese Boleta del Alumno: ");

    // Buscamos el objeto real en la lista (puntero)
    Alumno* alu = alumnos.buscar(boleta);

    if (alu != nullptr) {
        cout << "Alumno encontrado: " << alu->getNombreCompleto() << endl;
        cout << "Grupo actual: " << alu->getIdGrupoInscrito() << endl;

        grupos.listar(); // Mostramos opciones

        string idGrupo = Validaciones::pedirCadena("Ingrese ID del Grupo a inscribir: ");

        if (grupos.existe(idGrupo)) {
            alu->setIdGrupoInscrito(idGrupo);
            alu->setEstatusInscrito(true);

            // Guardamos cambios inmediatamente
            alumnos.guardarEnArchivo();
            cout << ">> Inscripcion realizada correctamente." << endl;
        } else {
            cout << ">> Error: El grupo no existe." << endl;
        }
    } else {
        cout << ">> Error: Alumno no encontrado." << endl;
    }
}

void GestionEscolar::buscarAlumno() {
    string boleta = Validaciones::pedirCadena("Ingrese Boleta: ");
    Alumno* alu = alumnos.buscar(boleta);
    if (alu) {
        cout << "-------------------------" << endl;
        cout << "Boleta: " << alu->getBoleta() << endl;
        cout << "Nombre: " << alu->getNombreCompleto() << endl;
        cout << "Grupo:  " << alu->getIdGrupoInscrito() << endl;
        cout << "Ciclo:  " << alu->getNombreCiclo() << endl;
        cout << "-------------------------" << endl;
    } else {
        cout << ">> No encontrado." << endl;
    }
}

void GestionEscolar::darBajaAlumno() {
    string boleta = Validaciones::pedirCadena("Ingrese Boleta a eliminar: ");
    // La lista se encarga de reestructurar punteros y liberar memoria
    alumnos.eliminar(boleta);
    // Guardamos la nueva estructura en disco
    alumnos.guardarEnArchivo();
}

// --- GESTIÓN DE PROFESORES ---

void GestionEscolar::menuProfesores() {
    int opc;
    do {
        cout << "\n--- MENU PROFESORES ---" << endl;
        cout << "1. Registrar Profesor" << endl;
        cout << "2. Ver Lista de Profesores" << endl;
        cout << "0. Regresar" << endl;
        opc = Validaciones::pedirEntero("Opcion: ", 0, 2);

        switch(opc) {
            case 1: registrarProfesor(); break;
            case 2: profesores.listar(); break;
        }
    } while(opc != 0);
}

void GestionEscolar::registrarProfesor() {
    Profesor p;
    p.setNombreCompleto(Validaciones::pedirCadena("Nombre Completo: "));
    p.setCedula(Validaciones::pedirCadena("Cedula Profesional: "));
    p.setBoletaTrabajador(generarBoletaProfesor());

    profesores.insertarInicio(p);
    profesores.guardarEnArchivo();

    cout << ">> Profesor registrado: " << p.getBoletaTrabajador() << endl;
}

// --- (Opcional) Funciones para crear grupos/ciclos desde menú ---
// Se implementarian de forma similar usando Validaciones y lista.insertar()