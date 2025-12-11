#include "../../include/Utilidades/Validaciones.h"
#include <cctype> // Para isdigit

namespace Validaciones {

    // --- Implementación de Validaciones Lógicas ---

    bool esNumero(const string& s) {
        if (s.empty()) return false;
        for (char c : s) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

    bool esFechaValida(const Fecha& f) {
        if (f.anio < 1900 || f.anio > 2100) return false;
        if (f.mes < 1 || f.mes > 12) return false;

        int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // Verificación de año bisiesto
        if ((f.anio % 4 == 0 && f.anio % 100 != 0) || (f.anio % 400 == 0)) {
            diasPorMes[2] = 29;
        }

        if (f.dia < 1 || f.dia > diasPorMes[f.mes]) return false;

        return true;
    }

    bool esCorreoValido(const string& email) {
        // Validación simple: debe tener '@' y luego un '.'
        size_t atPos = email.find('@');
        size_t dotPos = email.find('.', atPos);
        return (atPos != string::npos && dotPos != string::npos);
    }

    void limpiarBuffer() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // --- Implementación de Helpers de Captura ---

    int pedirEntero(string mensaje, int min, int max) {
        int valor;
        while (true) {
            cout << mensaje;
            if (cin >> valor) {
                if (valor >= min && valor <= max) {
                    limpiarBuffer(); // Limpiar el Enter que queda en el buffer
                    return valor;
                } else {
                    cout << "Error: El valor debe estar entre " << min << " y " << max << ".\n";
                }
            } else {
                cout << "Error: Ingrese un numero valido.\n";
                cin.clear(); // Restaura el estado de cin
                limpiarBuffer();
            }
        }
    }

    string pedirCadena(string mensaje) {
        string entrada;
        while (true) {
            cout << mensaje;
            getline(cin, entrada);
            // Puedes agregar trim() aqui si quieres quitar espacios
            if (!entrada.empty()) {
                return entrada;
            }
            cout << "Error: El campo no puede estar vacio.\n";
        }
    }

    Fecha pedirFecha(string mensaje) {
        Fecha f;
        bool valida = false;
        cout << mensaje << endl;
        do {
            f.dia = pedirEntero("   Dia: ", 1, 31);
            f.mes = pedirEntero("   Mes: ", 1, 12);
            f.anio = pedirEntero("   Anio (1900-2100): ", 1900, 2100);

            if (esFechaValida(f)) {
                valida = true;
            } else {
                cout << "Error: Fecha logica incorrecta (ej. 30 de Febrero). Intente de nuevo.\n";
            }
        } while (!valida);
        return f;
    }
}