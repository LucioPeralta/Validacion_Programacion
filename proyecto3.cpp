#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <cctype>
using namespace std;

const int MAX_FILAS = 10;
const int MAX_COLUMNAS = 10;

struct Paciente {
    string nombre;
    int edad;
    string dni;
    int diasInternado;
};

Paciente hospital[MAX_FILAS][MAX_COLUMNAS];
int filas = 0, columnas = 0;

// -------- VALIDACIONES --------
bool textoValido(const string& entrada) {
    if (entrada.empty()) return false;
    for (char c : entrada)
        if (!isalpha(c) && c != ' ') return false; // Solo letras y espacios
    return true;
}

bool dniValido(const string& dni) {
    if (dni.length() != 8) return false; // Debe tener exactamente 8 caracteres
    for (char c : dni)
        if (!isdigit(c)) return false; // Todos los caracteres deben ser dígitos
    return true;
}

int leerEntero(string mensaje, int min = 0, int max = 100) {
    string entrada;
    int valor;
    while (true) {
        cout << mensaje;
        cin >> entrada;

        // Validar que la entrada sea un número entero
        bool esNumero = true;
        for (char c : entrada) {
            if (!isdigit(c)) {
                esNumero = false;
                break;
            }
        }

        if (esNumero) {
            try {
                valor = stoi(entrada);
                if (valor < min || valor > max) throw invalid_argument("Fuera de rango");
                return valor;
            } catch (...) {
                cout << "Entrada inválida. Ingrese un número entero entre " << min << " y " << max << ".\n";
            }
        } else {
            cout << "Entrada inválida. Solo se permiten números enteros.\n";
        }
    }
}

string leerTexto(string mensaje) {
    string entrada;
    while (true) {
        cout << mensaje;
        getline(cin >> ws, entrada); // Leer con espacios
        if (!textoValido(entrada)) {
            cout << "Entrada inválida. Solo se permiten letras y espacios. Intente de nuevo.\n";
        } else {
            return entrada;
        }
    }
}

string leerDNI(string mensaje) {
    string entrada;
    while (true) {
        cout << mensaje;
        cin >> entrada;
        if (!dniValido(entrada)) {
            cout << "Entrada inválida. El DNI debe tener exactamente 8 dígitos. Intente de nuevo.\n";
        } else {
            return entrada;
        }
    }
}

// -------- CARGA DE DATOS --------
void cargarPacientes() {
    filas = leerEntero("Ingrese cantidad de filas de camas (máx 10): ", 1, MAX_FILAS);
    columnas = leerEntero("Ingrese cantidad de columnas de camas (máx 10): ", 1, MAX_COLUMNAS);

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << "\nPaciente en cama (" << i << "," << j << "):\n";
            hospital[i][j].nombre = leerTexto("Nombre: ");
            hospital[i][j].edad = leerEntero("Edad: ", 0, 120);
            hospital[i][j].dni = leerDNI("DNI: ");
            hospital[i][j].diasInternado = leerEntero("Días internado: ", 0, numeric_limits<int>::max());
        }
    }
}

// -------- FUNCIONES --------
float calcularPromedioEdad() {
    int suma = 0;
    int total = filas * columnas;
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            suma += hospital[i][j].edad;
    return static_cast<float>(suma) / total;
}

void generarArchivoDiasInternado() {
    ofstream archivo("internados_mas_5_dias.txt");
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            if (hospital[i][j].diasInternado > 5)
                archivo << hospital[i][j].nombre << endl;
    archivo.close();
    cout << "Archivo 'internados_mas_5_dias.txt' generado.\n";
}

void generarArchivoMayoresAlPromedio(float promedio) {
    ofstream archivo("mayores_al_promedio.txt");
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            if (hospital[i][j].edad > promedio)
                archivo << hospital[i][j].nombre << " - DNI: " << hospital[i][j].dni << endl;
    archivo.close();
    cout << "Archivo 'mayores_al_promedio.txt' generado.\n";
}

void mostrarPacientePorPosicion() {
    int i = leerEntero("Fila de la cama: ", 0);
    int j = leerEntero("Columna de la cama: ", 0);
    if (i < filas && j < columnas) {
        Paciente p = hospital[i][j];
        cout << "\nDatos del paciente en (" << i << "," << j << "):\n";
        cout << "Nombre: " << p.nombre << "\nEdad: " << p.edad << "\nDNI: " << p.dni << "\nDías internado: " << p.diasInternado << endl;
    } else {
        cout << "Ubicación inválida.\n";
    }
}

void pacientesAdyacentes(int i, int j) {
    ofstream archivo("pacientes_adyacentes.txt");
    int contador = 0;

    for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++) {
            int ni = i + dx;
            int nj = j + dy;
            if ((dx != 0 || dy != 0) && ni >= 0 && ni < filas && nj >= 0 && nj < columnas) {
                archivo << hospital[ni][nj].nombre << endl;
                contador++;
            }
        }

    archivo.close();
    cout << "Hay " << contador << " pacientes adyacentes al infectado en (" << i << "," << j << ").\n";
    cout << "Archivo 'pacientes_adyacentes.txt' generado.\n";
}

void mostrarGraficoCamas() {
    cout << "\n--- Gráfico de camas ---\n";
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << "[";
            if (!hospital[i][j].nombre.empty()) {
                cout << hospital[i][j].nombre.substr(0, 3); // Mostrar las primeras 3 letras del nombre
            } else {
                cout << "VAC"; // Indicar que la cama está vacía
            }
            cout << "] ";
        }
        cout << endl;
    }
    cout << "\nLeyenda: 'VAC' indica cama vacía.\n";
}

// -------- MENÚ --------
void menu() {
    int opcion;
    float promedio;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Calcular promedio de edad\n";
        cout << "2. Generar archivo de pacientes con más de 5 días internados\n";
        cout << "3. Generar archivo de pacientes mayores al promedio\n";
        cout << "4. Mostrar paciente por posición\n";
        cout << "5. Mostrar pacientes adyacentes a uno infectado\n";
        cout << "6. Mostrar gráfico de camas\n"; // Nueva opción
        cout << "0. Salir\n";
        opcion = leerEntero("Opción: ", 0);

        switch (opcion) {
            case 1:
                promedio = calcularPromedioEdad();
                cout << "Promedio de edad: " << promedio << endl;
                break;
            case 2:
                generarArchivoDiasInternado();
                break;
            case 3:
                promedio = calcularPromedioEdad();
                generarArchivoMayoresAlPromedio(promedio);
                break;
            case 4:
                mostrarPacientePorPosicion();
                break;
            case 5: {
                int i = leerEntero("Fila del infectado: ", 0);
                int j = leerEntero("Columna del infectado: ", 0);
                if (i < filas && j < columnas)
                    pacientesAdyacentes(i, j);
                else
                    cout << "Posición inválida.\n";
                break;
            }
            case 6:
                mostrarGraficoCamas();
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

// -------- MAIN --------
int main() {
    cargarPacientes();
    menu();
    return 0;
}
