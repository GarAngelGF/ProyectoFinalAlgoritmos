#include "../../include/Estructuras/EstructCiclos.h"

ListaCiclos::ListaCiclos() : cabeza(nullptr) {}

ListaCiclos::~ListaCiclos() {
    while (cabeza) {
        NodoCiclo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

// --- INSERTAR (Insertar al inicio para simplicidad) ---
void ListaCiclos::insertar(Ciclo c) {
    NodoCiclo* nuevo = new NodoCiclo(c);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

// --- OBTENER CICLO ACTUAL ---
string ListaCiclos::obtenerCicloActual() {
    NodoCiclo* temp = cabeza;
    while(temp) {
        if(temp->dato.isActivo()) return temp->dato.getNombreCiclo();
        temp = temp->siguiente;
    }
    return "SIN_CICLO";
}

// --- LISTAR ---
void ListaCiclos::listar() {
    NodoCiclo* temp = cabeza;
    cout << "--- CICLOS ESCOLARES (Lista Simple) ---" << endl;
    if (!cabeza) cout << "(Vacio)" << endl;

    while(temp) {
        cout << "Ciclo: " << temp->dato.getNombreCiclo()
             << " [" << (temp->dato.isActivo() ? "ACTIVO" : "CERRADO") << "]" << endl;
        temp = temp->siguiente;
    }
}

// --- PERSISTENCIA JSON ---

void ListaCiclos::guardarEnArchivo() {
    ofstream archivo("data/ciclos.json");
    if (!archivo.is_open()) return;

    archivo << "[\n";
    NodoCiclo* temp = cabeza;
    while (temp) {
        archivo << "  {\n";
        archivo << "    \"nombre\": \"" << temp->dato.getNombreCiclo() << "\",\n";
        // Guardamos las fechas formateadas simple para referencia en el archivo
        archivo << "    \"inicio\": \"" << temp->dato.getInicio().dia << "/"
                                      << temp->dato.getInicio().mes << "/"
                                      << temp->dato.getInicio().anio << "\",\n";
        archivo << "    \"fin\": \"" << temp->dato.getFin().dia << "/"
                                   << temp->dato.getFin().mes << "/"
                                   << temp->dato.getFin().anio << "\",\n";
        archivo << "    \"activo\": \"" << (temp->dato.isActivo() ? "1" : "0") << "\"\n";
        archivo << "  }";

        if (temp->siguiente) archivo << ","; // Coma si no es el último
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

    // Limpiar comillas
    size_t firstQuote = valor.find('\"');
    size_t lastQuote = valor.rfind('\"');

    if (firstQuote != string::npos && lastQuote != string::npos && lastQuote > firstQuote) {
        return valor.substr(firstQuote + 1, lastQuote - firstQuote - 1);
    }
    return "";
}

void ListaCiclos::cargarDeArchivo() {
    ifstream archivo("data/ciclos.json");
    if (!archivo.is_open()) return;

    string linea;
    Ciclo cActual;
    bool leyendoObjeto = false;

    while (getline(archivo, linea)) {
        if (linea.find("{") != string::npos) {
            leyendoObjeto = true;
            cActual = Ciclo(); // Reset
            // Inicializamos fechas en 0 por si no vienen en el JSON
            cActual.setInicio({0,0,0});
            cActual.setFin({0,0,0});
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
            // Nota: Para este ejemplo no parseamos las fechas de vuelta desde el string "dd/mm/aaaa"
            // para mantener la simplicidad, pero se guardan para que el humano las lea.
        }
    }
    archivo.close();
}