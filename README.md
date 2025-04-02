#Requisitos Previos
###Antes de compilar y ejecutar el proyecto, asegúrate de cumplir con los siguientes requisitos:

###Compilador C++:

####Se requiere un compilador compatible con C++17, como g++ (GCC) o clang++.
###Bibliotecas Externas:

###Boost Library:
###Descarga e instala Boost desde Boost Downloads.
https://www.boost.org/users/download/
###Asegúrate de que la ruta de instalación de Boost esté configurada correctamente en el archivo make2.mak:

####Abseil Library:
####Descarga e instala Abseil desde Abseil GitHub.
https://github.com/abseil/abseil-cpp
####Asegúrate de que la ruta de instalación de Abseil esté configurada correctamente en el archivo make2.mak:
Ejemplo: INCLUDES = -IC:/Users/Rafael/abseil-cpp-master -IC:/Users/Rafael/boost_1_87_0
###Sistema Operativo:

####El proyecto está diseñado para sistemas basados en Unix (Linux/MacOS) o Windows con un entorno compatible como MinGW o WSL.
####Compatibilidad:
En sistemas Windows, asegúrate de tener un entorno compatible como MinGW o WSL para ejecutar los comandos make y rm.

Makefile es el compilador a modificar para ejecutar el ejercicio.cpp donde esta el cuadro comparativo entre las dos estructuras
El make2 es el compílador de los dos programas btree_map.hpp y flatmap.hpp para mostrar el comportamiento individual de ambos
solo se deben modificar las rutas por los makes
