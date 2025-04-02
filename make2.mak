# Nombre del compilador
CXX = g++

# Estándar de C++
CXXFLAGS = -std=c++17 -Wall -O2

# Rutas de inclusión
INCLUDES = -IC:/Users/Rafael/boost_1_87_0 -IC:/Users/Rafael/abseil-cpp-master

# Archivos fuente y ejecutables
BTREE_SRC = btree.cpp
FLATMAP_SRC = flatMap.cpp
BTREE_EXE = btree
FLATMAP_EXE = flatMap

# Regla principal: compilar y ejecutar ambos programas
all: $(BTREE_EXE) $(FLATMAP_EXE)
	@echo "========================================"
	@echo "EJECUTANDO BTREE PROGRAM"
	@echo "========================================"
	./$(BTREE_EXE)
	@echo ""
	@echo "========================================"
	@echo "EJECUTANDO FLATMAP PROGRAM"
	@echo "========================================"
	./$(FLATMAP_EXE)

# Regla para compilar btree.cpp
$(BTREE_EXE): $(BTREE_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(BTREE_EXE) $(BTREE_SRC)

# Regla para compilar flatMap.cpp
$(FLATMAP_EXE): $(FLATMAP_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(FLATMAP_EXE) $(FLATMAP_SRC)

# Regla para limpiar los ejecutables generados
clean:
	rm -f $(BTREE_EXE) $(FLATMAP_EXE)