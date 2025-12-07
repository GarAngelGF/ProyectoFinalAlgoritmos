cmake_minimum_required(VERSION 4.0)
project(ProyectoFinalAlgoritmos)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProyectoFinalAlgoritmos main.cpp
        Include/Utilidades/Validaciones.h
        Include/Utilidades/Comunes.h
        Include/Modelos/Alumno.h
        Include/Modelos/Profesor.h
        Include/Modelos/Grupo.h
        Include/Modelos/Ciclo.h
        Include/Estructuras/EstructAlumno.h
        Include/Estructuras/EstructProfe.h
        Include/Estructuras/EstructGrupos.h
        Include/Estructuras/EstructCiclos.h
        Include/Controladores/GestionEscolar.h
        src/Controladores/GestionEscolar.cpp
        src/Estructuras/EstructAlumno.cpp
        src/Estructuras/EstructCiclos.cpp
        src/Estructuras/EstructGrupos.cpp
        src/Estructuras/EstructProfe.cpp
        src/Modelos/Alumno.cpp
        src/Modelos/Ciclo.cpp
        src/Modelos/Grupo.cpp
        src/Modelos/Profesor.cpp
        src/Utilidades/Comunes.cpp
        src/Utilidades/Validaciones.cpp
)
