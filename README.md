# Proyecto de Gestión de Pacientes en un Hospital

Este proyecto es un programa en C++ que permite gestionar la información de pacientes en un hospital. El programa organiza las camas en una habitación rectangular y permite registrar y visualizar datos como el nombre, edad, DNI y días internados de cada paciente.

## Requisitos para ejecutar el proyecto

Para ejecutar este proyecto, necesitas lo siguiente:

1. **Compilador de C++**: Asegúrate de tener instalado un compilador como `g++` (parte de GCC).
2. **Sistema operativo**: Este proyecto está diseñado para ejecutarse en sistemas Linux, pero también puede funcionar en otros sistemas operativos con un compilador compatible.
3. **Terminal**: Necesitarás una terminal para compilar y ejecutar el programa.

### Instalación de GCC en Linux

Si no tienes GCC instalado, puedes instalarlo ejecutando el siguiente comando en tu terminal:

```bash
sudo apt update
sudo apt install build-essential
```

### Pasos para compilar y ejecutar el proyecto

1. Abre una terminal y navega a la carpeta donde se encuentra el archivo proyecto3.cpp. Por ejemplo:

```bash
cd ~/carpeta_del_proyecto
```

2. Compila el archivo fuente con el siguiente comando:

```bash
g++ proyecto3.cpp -o proyecto3
```
Esto generará un archivo ejecutable llamado proyecto3.

3. Ejecuta el programa con el siguiente comando:

```bash
./proyecto3
```