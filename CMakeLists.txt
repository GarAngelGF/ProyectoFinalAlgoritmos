cmake_minimum_required(VERSION 4.0)
project(Nueva_carpeta__2_)

set(CMAKE_CXX_STANDARD 14)

include_directories(Data)
include_directories(Include)
include_directories(Include/Controladores)
include_directories(Include/Estructuras)
include_directories(Include/Modelos)
include_directories(Include/Utilidades)
include_directories(src)

add_executable(Nueva_carpeta__2_
        Data/ReadMe.txt
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
