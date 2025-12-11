#include "../../include/Controladores/GestionEscolar.h"

// AGREGADO: Librerías para asegurar que la carpeta Data exista al iniciar
#ifdef _WIN32
#include <direct.h> // Para _mkdir en Windows
#else
#include <sys/stat.h> // Para mkdir en Linux/Mac
#endif

// Constructor
GestionEscolar::GestionEscolar() {
    srand(time(0)); // Semilla para aleatorios
}

// --- UTILIDADES DE UI ---
void GestionEscolar::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void GestionEscolar::pausar() {
    cout << "\n";
    Validaciones::pedirCadena("Presione Enter para continuar...");
}

// --- INICIALIZACIÓN ---
void GestionEscolar::inicializarSistema() {
    limpiarPantalla();

    // CAMBIO: Asegurar que la carpeta Data exista antes de cargar nada
    // Esto previene errores si es la primera vez que se ejecuta el programa
#ifdef _WIN32
    _mkdir("Data");
#else
    mkdir("Data", 0777);
#endif

    cout << ">> Cargando sistema y archivos JSON desde carpeta 'Data'..." << endl;

    ciclos.cargarDeArchivo();
    grupos.cargarDeArchivo();
    profesores.cargarDeArchivo();
    alumnos.cargarDeArchivo();

    // Si no hay ciclos (primera ejecución), cargamos datos por defecto
    if (ciclos.obtenerCicloActual() == "SIN_CICLO") {
        cargarDatosIniciales();
    }
}

void GestionEscolar::cargarDatosIniciales() {
    cout << ">> Inicializando datos por defecto..." << endl;

    Ciclo c;
    c.setNombreCiclo("2024-2025");
    c.setActivo(true);
    c.setInicio({ 1,8,2024 });
    c.setFin({ 15,7,2025 });
    ciclos.insertar(c);
    ciclos.guardarEnArchivo(); // Esto creará el archivo en Data/ciclos.json

    grupos.insertar(Grupo("1MA", 1, 'M', 'A'));
    grupos.guardarEnArchivo(); // Esto creará el archivo en Data/grupos.json
}

// --- GENERADORES ID ---
string GestionEscolar::generarBoletaAlumno() {
    string ciclo = ciclos.obtenerCicloActual();
    string anio = (ciclo.length() >= 4) ? ciclo.substr(0, 4) : "2024";
    string randomPart = to_string(rand() % 900000 + 100000);
    return anio + randomPart;
}

string GestionEscolar::generarBoletaProfesor() {
    return "DOC-" + to_string(rand() % 90000 + 10000);
}

// --- NUEVO: REPORTE GENERAL ---
void GestionEscolar::generarReporteGeneral() {
    limpiarPantalla();
    cout << "========================================" << endl;
    cout << "      REPORTE GENERAL DEL SISTEMA" << endl;
    cout << "========================================" << endl;

    cout << "\n>>> 1. CICLOS ESCOLARES REGISTRADOS <<<" << endl;
    ciclos.listar();

    cout << "\n>>> 2. GRUPOS REGISTRADOS <<<" << endl;
    grupos.listar();

    cout << "\n>>> 3. PROFESORES REGISTRADOS <<<" << endl;
    profesores.listar();

    cout << "\n>>> 4. ALUMNOS REGISTRADOS <<<" << endl;
    alumnos.listar(false); // false para mostrar todos (incluyendo bajas)

    cout << "\n========================================" << endl;
    cout << "          FIN DEL REPORTE" << endl;
    cout << "========================================" << endl;
}

// --- MENÚ PRINCIPAL ---
void GestionEscolar::menuPrincipal() {
    int opc;
    do {
        limpiarPantalla();
        cout << "===============================" << endl;
        cout << "   SISTEMA DE CONTROL ESCOLAR" << endl;
        cout << "===============================" << endl;
        cout << "1. Gestion de Alumnos" << endl;
        cout << "2. Gestion de Profesores" << endl;
        cout << "3. Gestion de Grupos" << endl;
        cout << "4. Gestion de Ciclos Escolares" << endl;
        cout << "5. Generar Reporte General" << endl;
        cout << "0. Salir" << endl;
        cout << "===============================" << endl;

        opc = Validaciones::pedirEntero("Seleccione una opcion: ", 0, 5);

        switch (opc) {
        case 1: menuAlumnos(); break;
        case 2: menuProfesores(); break;
        case 3: menuGrupos(); break;
        case 4: menuCiclos(); break;
        case 5: generarReporteGeneral(); pausar(); break;
        case 0: cout << "Saliendo..." << endl; break;
        }
    } while (opc != 0);
}

// ==========================================
//           GESTIÓN DE ALUMNOS
// ==========================================

void GestionEscolar::menuAlumnos() {
    int opc;
    do {
        limpiarPantalla();
        cout << "--- MENU ALUMNOS ---" << endl;
        cout << "1. Registrar Nuevo Alumno" << endl;
        cout << "2. Inscribir Alumno a Grupo" << endl;
        cout << "3. Buscar Alumno" << endl;
        cout << "4. Dar de Baja" << endl;
        cout << "5. Listar Todos los Registros" << endl;
        cout << "0. Regresar" << endl;

        opc = Validaciones::pedirEntero("Opcion: ", 0, 5);

        switch (opc) {
        case 1: registrarAlumno(); pausar(); break;
        case 2: inscribirAlumno(); pausar(); break;
        case 3: buscarAlumno(); pausar(); break;
        case 4: darBajaAlumno(); pausar(); break;
        case 5: alumnos.listar(false); pausar(); break;
        }
    } while (opc != 0);
}

void GestionEscolar::registrarAlumno() {
    limpiarPantalla();
    cout << "--- REGISTRO DE ALUMNO ---" << endl;
    Alumno nuevo;

    nuevo.setNombreCompleto(Validaciones::pedirCadena("Nombre Completo: "));
    nuevo.setCurp(Validaciones::pedirCadena("CURP: "));

    char genero;
    cout << "Genero (M/F): "; cin >> genero; Validaciones::limpiarBuffer();
    nuevo.setGenero(genero);

    nuevo.setNacimiento(Validaciones::pedirFecha("Fecha de Nacimiento"));

    Tutor t;
    t.nombre = Validaciones::pedirCadena("Nombre del Tutor: ");
    t.parentesco = Validaciones::pedirCadena("Parentesco: ");
    t.telefono = Validaciones::pedirCadena("Telefono Tutor: ");
    nuevo.setTutor(t);

    nuevo.setBoleta(generarBoletaAlumno());
    nuevo.setNombreCiclo(ciclos.obtenerCicloActual());
    nuevo.setIdGrupoInscrito("SIN_ASIGNAR");
    nuevo.setEstatusInscrito(false);

    alumnos.insertar(nuevo);
    alumnos.guardarEnArchivo();

    cout << ">> Alumno registrado con EXITO. Boleta: " << nuevo.getBoleta() << endl;
}

void GestionEscolar::inscribirAlumno() {
    string boleta = Validaciones::pedirCadena("Ingrese Boleta del Alumno: ");
    Alumno* alu = alumnos.buscar(boleta);

    if (alu != nullptr) {
        cout << "Alumno: " << alu->getNombreCompleto() << endl;

        cout << "\nGrupos disponibles:" << endl;
        grupos.listar();

        string idGrupo = Validaciones::pedirCadena("Ingrese ID del Grupo: ");

        if (grupos.existe(idGrupo)) {
            alu->setIdGrupoInscrito(idGrupo);
            alu->setEstatusInscrito(true);
            alumnos.guardarEnArchivo();
            cout << ">> Inscripcion realizada." << endl;
        }
        else {
            cout << ">> Error: Grupo no existe." << endl;
        }
    }
    else {
        cout << ">> Error: Alumno no encontrado." << endl;
    }
}

void GestionEscolar::buscarAlumno() {
    string boleta = Validaciones::pedirCadena("Ingrese Boleta a buscar: ");
    Alumno* alu = alumnos.buscar(boleta);

    if (alu) {
        cout << "\n--- RESULTADO ---" << endl;
        cout << "Boleta: " << alu->getBoleta() << endl;
        cout << "Nombre: " << alu->getNombreCompleto() << endl;
        cout << "Grupo:  " << alu->getIdGrupoInscrito() << endl;
        cout << "Estado: " << (alu->getEstatusInscrito() ? "Activo" : "Inactivo") << endl;
    }
    else {
        cout << ">> No encontrado." << endl;
    }
}

void GestionEscolar::darBajaAlumno() {
    string boleta = Validaciones::pedirCadena("Ingrese Boleta a eliminar: ");
    alumnos.eliminar(boleta);
    alumnos.guardarEnArchivo();
}

// ==========================================
//           GESTIÓN DE PROFESORES
// ==========================================

void GestionEscolar::menuProfesores() {
    int opc;
    do {
        limpiarPantalla();
        cout << "--- MENU PROFESORES ---" << endl;
        cout << "1. Registrar Profesor" << endl;
        cout << "2. Buscar Profesor" << endl;
        cout << "3. Listar Todos los Registros" << endl;
        cout << "0. Regresar" << endl;
        opc = Validaciones::pedirEntero("Opcion: ", 0, 3);

        switch (opc) {
        case 1: registrarProfesor(); pausar(); break;
        case 2: buscarProfesor(); pausar(); break;
        case 3: profesores.listar(); pausar(); break;
        }
    } while (opc != 0);
}

void GestionEscolar::registrarProfesor() {
    limpiarPantalla();
    cout << "--- REGISTRO DE PROFESOR ---" << endl;
    Profesor p;

    p.setNombreCompleto(Validaciones::pedirCadena("Nombre Completo: "));
    p.setTelefono(Validaciones::pedirCadena("Telefono: "));
    p.setBoletaTrabajador(generarBoletaProfesor());

    cout << "\nSeleccione el Grupo Titular:" << endl;
    grupos.listar();
    cout << "NOTA: Escriba '0' si no sera titular." << endl;

    bool grupoValido = false;
    do {
        string idG = Validaciones::pedirCadena("ID Grupo: ");
        if (idG == "0") {
            p.setIdGrupoTitular("SIN_ASIGNAR");
            grupoValido = true;
        }
        else if (grupos.existe(idG)) {
            p.setIdGrupoTitular(idG);
            grupoValido = true;
        }
        else {
            cout << ">> Error: El grupo no existe. Intente de nuevo." << endl;
        }
    } while (!grupoValido);

    profesores.insertar(p);
    profesores.guardarEnArchivo();

    cout << ">> Profesor registrado: " << p.getBoletaTrabajador()
        << " | Titular de: " << p.getIdGrupoTitular() << endl;
}

void GestionEscolar::buscarProfesor() {
    string boleta = Validaciones::pedirCadena("Ingrese Boleta Docente: ");
    Profesor* p = profesores.buscar(boleta);

    if (p) {
        cout << "\n--- DATOS PROFESOR ---" << endl;
        cout << "Boleta:  " << p->getBoletaTrabajador() << endl;
        cout << "Nombre:  " << p->getNombreCompleto() << endl;
        cout << "Titular: " << p->getIdGrupoTitular() << endl;
    }
    else {
        cout << ">> Profesor no encontrado." << endl;
    }
}

// ==========================================
//           GESTIÓN DE GRUPOS
// ==========================================

void GestionEscolar::menuGrupos() {
    int opc;
    do {
        limpiarPantalla();
        cout << "--- MENU GRUPOS ---" << endl;
        cout << "1. Listar Registros de Grupos" << endl;
        cout << "2. Crear Nuevo Grupo" << endl;
        cout << "0. Regresar" << endl;
        opc = Validaciones::pedirEntero("Opcion: ", 0, 2);

        switch (opc) {
        case 1: grupos.listar(); pausar(); break;
        case 2: crearGrupo(); pausar(); break;
        }
    } while (opc != 0);
}

void GestionEscolar::crearGrupo() {
    cout << "\n--- CREAR GRUPO ---" << endl;
    string id = Validaciones::pedirCadena("ID del Grupo (ej. 1MA): ");

    if (grupos.existe(id)) {
        cout << ">> Error: Ese ID de grupo ya existe." << endl;
        return;
    }

    int nivel = Validaciones::pedirEntero("Nivel (1-6): ", 1, 6);

    char turno;
    cout << "Turno (M/V): "; cin >> turno; Validaciones::limpiarBuffer();

    char secuencia;
    cout << "Secuencia (A, B, C...): "; cin >> secuencia; Validaciones::limpiarBuffer();

    Grupo g(id, nivel, turno, secuencia);
    grupos.insertar(g);
    grupos.guardarEnArchivo();

    cout << ">> Grupo creado exitosamente." << endl;
}

// ==========================================
//           GESTIÓN DE CICLOS
// ==========================================

void GestionEscolar::menuCiclos() {
    int opc;
    do {
        limpiarPantalla();
        cout << "--- MENU CICLOS ---" << endl;
        cout << "Ciclo Actual: " << ciclos.obtenerCicloActual() << endl;
        cout << "-------------------" << endl;
        cout << "1. Listar Registros de Ciclos" << endl;
        cout << "2. Crear Nuevo Ciclo" << endl;
        cout << "0. Regresar" << endl;
        opc = Validaciones::pedirEntero("Opcion: ", 0, 2);

        switch (opc) {
        case 1: ciclos.listar(); pausar(); break;
        case 2: crearCiclo(); pausar(); break;
        }
    } while (opc != 0);
}

void GestionEscolar::crearCiclo() {
    cout << "\n--- CREAR CICLO ESCOLAR ---" << endl;

    Ciclo c;
    c.setNombreCiclo(Validaciones::pedirCadena("Nombre del Ciclo (ej. 2025-2): "));

    cout << ">> Defina fecha de Inicio:" << endl;
    c.setInicio(Validaciones::pedirFecha("Fecha Inicio"));

    cout << ">> Defina fecha de Fin:" << endl;
    c.setFin(Validaciones::pedirFecha("Fecha Fin"));

    int activoInput = Validaciones::pedirEntero("¿Es el ciclo activo? (1=Si, 0=No): ", 0, 1);
    c.setActivo(activoInput == 1);

    ciclos.insertar(c);
    ciclos.guardarEnArchivo();

    cout << ">> Ciclo registrado." << endl;
}