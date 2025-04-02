# Nombre del compilador
CXX = g++

# Estándar de C++
CXXFLAGS = -std=c++17 -Wall -O2

# Rutas de inclusión
INCLUDES = -IC:/Users/Rafael/boost_1_87_0 -IC:/Users/Rafael/abseil-cpp-master

# Archivos fuente y ejecutable
SRC = ejercicio.cpp
EXE = ejercicio

# Regla principal
all: $(EXE)

$(EXE): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(EXE) $(SRC)

# Regla para limpiar archivos generados
clean:
	rm -f $(EXE)