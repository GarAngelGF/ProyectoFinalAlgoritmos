#include "../../include/Estructuras/EstructCiclos.h"
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

ListaCiclos::ListaCiclos() : cabeza(nullptr) {}

ListaCiclos::~ListaCiclos() {
    while (cabeza) {
        NodoCiclo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void ListaCiclos::insertar(Ciclo c) {
    NodoCiclo* nuevo = new NodoCiclo(c);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

string ListaCiclos::obtenerCicloActual() {
    NodoCiclo* temp = cabeza;
    while (temp) {
        if (temp->dato.isActivo()) return temp->dato.getNombreCiclo();
        temp = temp->siguiente;
    }
    return "SIN_CICLO";
}

void ListaCiclos::listar() {
    NodoCiclo* temp = cabeza;
    cout << "--- CICLOS ESCOLARES (Lista Simple) ---" << endl;
    if (!cabeza) cout << "(Vacio)" << endl;

    while (temp) {
        cout << "Ciclo: " << temp->dato.getNombreCiclo()
            << " [" << (temp->dato.isActivo() ? "ACTIVO" : "CERRADO") << "]"
            << " Inicio: " << temp->dato.getInicio().dia << "/" << temp->dato.getInicio().mes << "/" << temp->dato.getInicio().anio
            << endl;
        temp = temp->siguiente;
    }
}

// --- PERSISTENCIA JSON ---

void ListaCiclos::guardarEnArchivo() {
#ifdef _WIN32
    _mkdir("Data");
#else
    mkdir("Data", 0777);
#endif

    ofstream archivo("Data/ciclos.json");
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo crear el archivo Data/ciclos.json" << endl;
        return;
    }

    archivo << "[\n";
    NodoCiclo* temp = cabeza;
    while (temp) {
        archivo << "  {\n";
        archivo << "    \"nombre\": \"" << temp->dato.getNombreCiclo() << "\",\n";
        archivo << "    \"inicio\": \"" << temp->dato.getInicio().dia << "/"
            << temp->dato.getInicio().mes << "/"
            << temp->dato.getInicio().anio << "\",\n";
        archivo << "    \"fin\": \"" << temp->dato.getFin().dia << "/"
            << temp->dato.getFin().mes << "/"
            << temp->dato.getFin().anio << "\",\n";
        archivo << "    \"activo\": \"" << (temp->dato.isActivo() ? "1" : "0") << "\"\n";
        archivo << "  }";

        if (temp->siguiente) archivo << ",";
        archivo << "\n";

        temp = temp->siguiente;
    }
    archivo << "]";
    archivo.close();
}

string ListaCiclos::extraerValorJson(string linea) {
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

void ListaCiclos::cargarDeArchivo() {
    ifstream archivo("Data/ciclos.json"); // Ruta actualizada
    if (!archivo.is_open()) return;

    string linea;
    Ciclo cActual;
    bool leyendoObjeto = false;

    while (getline(archivo, linea)) {
        if (linea.find("{") != string::npos) {
            leyendoObjeto = true;
            cActual = Ciclo();
            cActual.setInicio({ 0,0,0 });
            cActual.setFin({ 0,0,0 });
        }
        else if (linea.find("}") != string::npos && leyendoObjeto) {
            insertar(cActual);
            leyendoObjeto = false;
        }
        else if (leyendoObjeto) {
            if (linea.find("\"nombre\"") != string::npos)
                cActual.setNombreCiclo(extraerValorJson(linea));

            else if (linea.find("\"activo\"") != string::npos) {
                string val = extraerValorJson(linea);
                cActual.setActivo(val == "1");
            }
            // Parseo de fechas corregido
            else if (linea.find("\"inicio\"") != string::npos) {
                string fechaStr = extraerValorJson(linea);
                stringstream ss(fechaStr);
                char slash;
                Fecha f;
                ss >> f.dia >> slash >> f.mes >> slash >> f.anio;
                cActual.setInicio(f);
            }
            else if (linea.find("\"fin\"") != string::npos) {
                string fechaStr = extraerValorJson(linea);
                stringstream ss(fechaStr);
                char slash;
                Fecha f;
                ss >> f.dia >> slash >> f.mes >> slash >> f.anio;
                cActual.setFin(f);
            }
        }
    }
    archivo.close();
}