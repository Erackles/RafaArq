#include <absl/container/btree_map.h>
#include <iostream>
#include <string>
#include <chrono> // Para medir tiempos

using namespace std;
using namespace std::chrono;

int main() {
    // Crear un btree_map
    absl::btree_map<int, std::string> myMap;

    const int numElements = 6; // Número de elementos reducido para mostrar paso a paso

    // Medir tiempo de inserción
    cout << "Inicio de insercion...\n";
    auto start = high_resolution_clock::now();
    for (int i = 0; i < numElements; ++i) {
        myMap[i] = "Value" + to_string(i);
        cout << "Insertando: " << i << " -> " << myMap[i] << endl;
    }
    auto end = high_resolution_clock::now();
    auto insertionTime = duration_cast<milliseconds>(end - start).count();
    cout << "Tiempo total de insercion: " << insertionTime << " ms\n" << endl;

    // Medir tiempo de búsqueda
    cout << "Inicio de busqueda...\n";
    int hits = 0;
    start = high_resolution_clock::now();
    for (int i = 0; i < numElements; ++i) {
        auto it = myMap.find(i);
        if (it != myMap.end()) {
            ++hits;
            cout << "Clave encontrada: " << it->first << " -> " << it->second << endl;
        } else {
            cout << "Clave no encontrada: " << i << endl;
        }
    }
    end = high_resolution_clock::now();
    auto searchTime = duration_cast<milliseconds>(end - start).count();
    cout << "Tiempo total de busqueda: " << searchTime << " ms\n" << endl;

    // Calcular tasa de aciertos
    double hitRate = static_cast<double>(hits) / numElements * 100;
    cout << "Tasa de aciertos: " << hitRate << "%\n" << endl;

    // Medir tiempo de eliminación
    cout << "Inicio de eliminacion...\n";
    start = high_resolution_clock::now();
    for (int i = 0; i < numElements; ++i) {
        myMap.erase(i);
        cout << "Eliminando clave: " << i << endl;
    }
    end = high_resolution_clock::now();
    auto deletionTime = duration_cast<milliseconds>(end - start).count();
    cout << "Tiempo total de eliminacion: " << deletionTime << " ms\n" << endl;

    return 0;
}