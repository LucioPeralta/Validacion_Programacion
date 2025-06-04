#include <iostream>      // Para entrada y salida estándar (cout, cin)
#include <string>        // Para usar el tipo string
#include <limits>        // Para obtener límites de tipos de datos (numeric_limits)
#include <fstream>       // Para manejo de archivos (ifstream, ofstream)
#include <cctype>        // Para funciones de caracteres (isalpha, isdigit)
using namespace std;

// Definición de las dimensiones máximas para la matriz de camas del hospital
const int MAX_FILAS = 10;
const int MAX_COLUMNAS = 10;

// Estructura que representa a un paciente con sus datos principales
struct Paciente {
    string nombre;
    int edad;
    string dni;
    int diasInternado;
};

// Matriz que almacena los pacientes en sus respectivas camas
Paciente hospital[MAX_FILAS][MAX_COLUMNAS];
int filas = 0, columnas = 0;

// -------- VALIDACIONES --------

// Esta función valida que el texto ingresado solo contenga letras y espacios.
// Retorna true si es válido, false si hay caracteres no permitidos o si está vacío.
bool textoValido(const string& entrada) {
    if (entrada.empty()) return false;
    for (char c : entrada)
        if (!isalpha(c) && c != ' ') return false;
    return true;
}

// Esta función valida que el DNI ingresado tenga exactamente 8 caracteres y que todos sean dígitos.
// Retorna true si cumple con el formato, false en caso contrario.
bool dniValido(const string& dni) {
    if (dni.length() != 8) return false;
    for (char c : dni)
        if (!isdigit(c)) return false;
    return true;
}

// Esta función lee un número entero desde la entrada estándar, mostrando un mensaje personalizado.
// Solo acepta números enteros dentro del rango [min, max]. Si la entrada es inválida, vuelve a pedirla.
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

// Esta función lee un texto desde la entrada estándar, mostrando un mensaje personalizado.
// Solo acepta textos que pasen la validación de textoValido (letras y espacios).
string leerTexto(string mensaje) {
    string entrada;
    while (true) {
        cout << mensaje;
        getline(cin >> ws, entrada);
        if (!textoValido(entrada)) {
            cout << "Entrada inválida. Solo se permiten letras y espacios. Intente de nuevo.\n";
        } else {
            return entrada;
        }
    }
}

// Esta función lee un DNI desde la entrada estándar, mostrando un mensaje personalizado.
// Solo acepta cadenas que pasen la validación de dniValido (exactamente 8 dígitos).
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

// Esta función permite cargar los datos de todos los pacientes del hospital.
// Solicita al usuario la cantidad de filas y columnas de camas, y luego pide los datos de cada paciente:
// nombre, edad, DNI y días internado. Los datos se almacenan en la matriz hospital.
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

// Calcula y retorna el promedio de edad de todos los pacientes registrados en el hospital.
float calcularPromedioEdad() {
    int suma = 0;
    int total = filas * columnas;
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            suma += hospital[i][j].edad;
    return static_cast<float>(suma) / total;
}

// Genera un archivo de texto con los nombres de los pacientes que llevan más de 5 días internados.
void generarArchivoDiasInternado() {
    ofstream archivo("internados_mas_5_dias.txt");
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            if (hospital[i][j].diasInternado > 5)
                archivo << hospital[i][j].nombre << endl;
    archivo.close();
    cout << "Archivo 'internados_mas_5_dias.txt' generado.\n";
}

// Genera un archivo de texto con los pacientes cuya edad es mayor al promedio.
// Incluye nombre y DNI de cada paciente.
void generarArchivoMayoresAlPromedio(float promedio) {
    ofstream archivo("mayores_al_promedio.txt");
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            if (hospital[i][j].edad > promedio)
                archivo << hospital[i][j].nombre << " - DNI: " << hospital[i][j].dni << endl;
    archivo.close();
    cout << "Archivo 'mayores_al_promedio.txt' generado.\n";
}

// Permite mostrar en pantalla los datos de un paciente según la posición (fila y columna) de la cama.
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

// Busca y guarda en un archivo los pacientes adyacentes a una cama específica (por ejemplo, un infectado).
// También muestra en pantalla la cantidad de pacientes adyacentes encontrados.
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

// Muestra un gráfico visual de las camas del hospital.
// Cada celda muestra las primeras 3 letras del nombre del paciente o "VAC" si la cama está vacía.
void mostrarGraficoCamas() {
    cout << "\n--- Gráfico de camas ---\n";
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << "[";
            if (!hospital[i][j].nombre.empty()) {
                cout << hospital[i][j].nombre.substr(0, 3);
            } else {
                cout << "VAC";
            }
            cout << "] ";
        }
        cout << endl;
    }
    cout << "\n'VAC' indica cama vacía.\n";
}

// -------- MENÚ --------

// Esta función muestra el menú principal del programa y permite al usuario seleccionar diferentes acciones.
// Según la opción elegida, se ejecutan funciones como calcular el promedio de edad, generar archivos,
// mostrar información de pacientes, o visualizar el gráfico de camas.
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
        cout << "6. Mostrar gráfico de camas\n";
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

// Función principal del programa. Primero carga los datos de los pacientes y luego muestra el menú principal.
int main() {
    cargarPacientes();
    menu();
    return 0;
}
