cmake_minimum_required(VERSION 4.0)
project(Proyecto_Final_Algoritmos_Equipo_6)

set(CMAKE_CXX_STANDARD 14)

include_directories(Data)
include_directories(Include)
include_directories(Include/Controladores)
include_directories(Include/Estructuras)
include_directories(Include/Modelos)
include_directories(Include/Utilidades)
include_directories(src)

add_executable(Proyecto_Final_Algoritmos_Equipo_6
        Include/Controladores/GestionEscolar.h
        Include/Estructuras/EstructAlumno.h
        Include/Estructuras/EstructCiclos.h
        Include/Estructuras/EstructGrupos.h
        Include/Estructuras/EstructProfe.h
        Include/Modelos/Alumno.h
        Include/Modelos/Ciclo.h
        Include/Modelos/Grupo.h
        Include/Modelos/Profesor.h
        Include/Utilidades/Comunes.h
        Include/Utilidades/Validaciones.h
        src/Controladores/GestionEscolar.cpp
        src/Estructuras/EstructAlumno.cpp
        src/Estructuras/EstructCiclos.cpp
        src/Estructuras/EstructGrupos.cpp
        src/Estructuras/EstructProfe.cpp
        src/Modelos/Alumno.cpp
        src/Modelos/Ciclo.cpp
        src/Modelos/Grupo.cpp
        src/Modelos/Profesor.cpp
        src/Utilidades/Validaciones.cpp
        main.cpp)

# --- Configuración de Instalación ---

# 1. Definir qué se va a instalar (tu ejecutable)
install(TARGETS Proyecto_Final_Algoritmos_Equipo_6 DESTINATION bin)

# 2. Configuración básica del instalador
set(CPACK_PACKAGE_NAME "SistemaControlEscolar")
set(CPACK_PACKAGE_VENDOR "Equipo6")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Sistema de Gestion Escolar - Proyecto Final")

# Generar instalador para Windows (NSIS) o archivo ZIP
set(CPACK_GENERATOR "NSIS") # Necesitas tener NSIS instalado, si no, usa "ZIP"

# Incluir el módulo CPack (siempre al final)
include(CPack)