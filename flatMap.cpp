#include <boost/container/flat_map.hpp>
#include <iostream>
#include <string>
#include <chrono> // Para medir tiempos

using namespace std;
using namespace std::chrono;

// Clase para manejar operaciones con flat_map
class FlatMapBenchmark {
private:
    boost::container::flat_map<int, string> myMap; // Estructura de datos
    int numElements;                               // Numero de elementos

public:
    // Constructor
    FlatMapBenchmark(int numElements) : numElements(numElements) {}

    // Metodo para insertar elementos
    void insertElements() {
        cout << "Inicio de insercion...\n";
        auto start = high_resolution_clock::now();
        for (int i = 0; i < numElements; ++i) {
            myMap[i] = "Value" + to_string(i);
            cout << "Insertando: " << i << " -> " << myMap[i] << endl;
        }
        auto end = high_resolution_clock::now();
        auto insertionTime = duration_cast<milliseconds>(end - start).count();
        cout << "Tiempo total de insercion: " << insertionTime << " ms\n" << endl;
    }

    // Metodo para buscar elementos
    void searchElements() {
        cout << "Inicio de busqueda...\n";
        int hits = 0;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < numElements; ++i) {
            auto it = myMap.find(i);
            if (it != myMap.end()) {
                ++hits;
                cout << "Clave encontrada: " << it->first << " -> " << it->second << endl;
            } else {
                cout << "Clave no encontrada: " << i << endl;
            }
        }
        auto end = high_resolution_clock::now();
        auto searchTime = duration_cast<milliseconds>(end - start).count();
        cout << "Tiempo total de busqueda: " << searchTime << " ms\n" << endl;

        // Calcular tasa de aciertos
        double hitRate = static_cast<double>(hits) / numElements * 100;
        cout << "Tasa de aciertos: " << hitRate << "%\n" << endl;
    }

    // Metodo para eliminar elementos
    void deleteElements() {
        cout << "Inicio de eliminacion...\n";
        auto start = high_resolution_clock::now();
        for (int i = 0; i < numElements; ++i) {
            myMap.erase(i);
            cout << "Eliminando clave: " << i << endl;
        }
        auto end = high_resolution_clock::now();
        auto deletionTime = duration_cast<milliseconds>(end - start).count();
        cout << "Tiempo total de eliminacion: " << deletionTime << " ms\n" << endl;
    }
};

int main() {
    const int numElements = 10; // Numero de elementos reducido para mostrar paso a paso

    // Crear una instancia de la clase FlatMapBenchmark
    FlatMapBenchmark benchmark(numElements);

    // Realizar las operaciones
    benchmark.insertElements();
    benchmark.searchElements();
    benchmark.deleteElements();

    return 0;
}