#include "../../include/Estructuras/EstructAlumno.h"
#ifdef _WIN32
#include <direct.h> // Para _mkdir en Windows
#else
#include <sys/stat.h> // Para mkdir en Linux/Mac
#endif

ListaAlumnos::ListaAlumnos() : cabeza(nullptr), cola(nullptr) {}

ListaAlumnos::~ListaAlumnos() {
    NodoAlumno* actual = cabeza;
    while (actual != nullptr) {
        NodoAlumno* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

// --- INSERTAR (Lista Doble) ---
void ListaAlumnos::insertar(Alumno alumno) {
    NodoAlumno* nuevo = new NodoAlumno(alumno);
    if (!cabeza) {
        cabeza = cola = nuevo;
    }
    else {
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    }
}

// --- ELIMINAR (Lista Doble) ---
void ListaAlumnos::eliminar(string boleta) {
    if (!cabeza) return;

    NodoAlumno* actual = cabeza;
    while (actual != nullptr) {
        if (actual->dato.getBoleta() == boleta) {
            if (actual == cabeza) {
                cabeza = actual->siguiente;
                if (cabeza) cabeza->anterior = nullptr;
                else cola = nullptr;
            }
            else if (actual == cola) {
                cola = actual->anterior;
                cola->siguiente = nullptr;
            }
            else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
            }
            delete actual;
            cout << ">> Alumno dado de baja correctamente." << endl;
            return;
        }
        actual = actual->siguiente;
    }
    cout << ">> Alumno no encontrado." << endl;
}

// --- BUSCAR (Lineal) ---
Alumno* ListaAlumnos::buscar(string boleta) {
    NodoAlumno* temp = cabeza;
    while (temp) {
        if (temp->dato.getBoleta() == boleta) return &temp->dato;
        temp = temp->siguiente;
    }
    return nullptr;
}

// --- LISTAR ---
void ListaAlumnos::listar(bool soloActivos) {
    NodoAlumno* temp = cabeza;
    cout << "--- LISTA ALUMNOS (Doble Enlace) ---" << endl;
    if (!cabeza) cout << "(Vacia)" << endl;

    while (temp) {
        bool mostrar = !soloActivos || temp->dato.getEstatusInscrito();
        if (mostrar) {
            cout << temp->dato.getBoleta() << " - " << temp->dato.getNombreCompleto()
                << " [" << (temp->dato.getEstatusInscrito() ? "ACTIVO" : "BAJA") << "]" << endl;
        }
        temp = temp->siguiente;
    }
}

// --- PERSISTENCIA JSON ---

void ListaAlumnos::guardarEnArchivo() {
    // 1. Crear carpeta Data si no existe
#ifdef _WIN32
    _mkdir("Data");
#else
    mkdir("Data", 0777);
#endif

    // 2. Guardar en la ruta Data/
    ofstream archivo("Data/alumnos.json");

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo crear el archivo Data/alumnos.json" << endl;
        return;
    }

    archivo << "[\n";
    NodoAlumno* temp = cabeza;
    while (temp) {
        archivo << "  {\n";
        archivo << "    \"boleta\": \"" << temp->dato.getBoleta() << "\",\n";
        archivo << "    \"nombre\": \"" << temp->dato.getNombreCompleto() << "\",\n";
        archivo << "    \"curp\": \"" << temp->dato.getCurp() << "\",\n";
        archivo << "    \"grupo\": \"" << temp->dato.getIdGrupoInscrito() << "\",\n";
        archivo << "    \"ciclo\": \"" << temp->dato.getNombreCiclo() << "\",\n";
        archivo << "    \"estatus\": \"" << (temp->dato.getEstatusInscrito() ? "1" : "0") << "\"\n";
        archivo << "  }";

        if (temp->siguiente) archivo << ",";
        archivo << "\n";

        temp = temp->siguiente;
    }
    archivo << "]";
    archivo.close();
}

string ListaAlumnos::extraerValorJson(string linea) {
    size_t posDosPuntos = linea.find(':');
    if (posDosPuntos == string::npos) return "";

    string valor = linea.substr(posDosPuntos + 1);
    size_t firstQuote = valor.find('\"');
    size_t lastQuote = valor.rfind('\"');

    if (firstQuote != string::npos && lastQuote != string::npos && lastQuote > firstQuote) {
        return valor.substr(firstQuote + 1, lastQuote - firstQuote - 1);
    }
    return "";
}

void ListaAlumnos::cargarDeArchivo() {
    ifstream archivo("Data/alumnos.json"); // Ruta actualizada
    if (!archivo.is_open()) return;

    string linea;
    Alumno aActual;
    bool leyendoObjeto = false;

    while (getline(archivo, linea)) {
        if (linea.find("{") != string::npos) {
            leyendoObjeto = true;
            aActual = Alumno();
            aActual.setEstatusInscrito(false);
            aActual.setIdGrupoInscrito("SIN_ASIGNAR");
        }
        else if (linea.find("}") != string::npos && leyendoObjeto) {
            insertar(aActual);
            leyendoObjeto = false;
        }
        else if (leyendoObjeto) {
            if (linea.find("\"boleta\"") != string::npos)
                aActual.setBoleta(extraerValorJson(linea));
            else if (linea.find("\"nombre\"") != string::npos)
                aActual.setNombreCompleto(extraerValorJson(linea));
            else if (linea.find("\"curp\"") != string::npos)
                aActual.setCurp(extraerValorJson(linea));
            else if (linea.find("\"grupo\"") != string::npos)
                aActual.setIdGrupoInscrito(extraerValorJson(linea));
            else if (linea.find("\"ciclo\"") != string::npos)
                aActual.setNombreCiclo(extraerValorJson(linea));
            else if (linea.find("\"estatus\"") != string::npos) {
                string val = extraerValorJson(linea);
                aActual.setEstatusInscrito(val == "1");
            }
        }
    }
    archivo.close();
}