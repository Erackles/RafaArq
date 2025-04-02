#include <iomanip> // Para formatear la salida
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include "C:/Users/Rafael/boost_1_87_0/boost/container/flat_map.hpp"
#include "C:/Users/Rafael/abseil-cpp-master/absl/container/btree_map.h"

using namespace std;
using namespace std::chrono;

// Generar claves aleatorias
vector<int> generateRandomKeys(size_t count, int min_value, int max_value)
{
    vector<int> keys(count);

    // Mezcla de random_device y tiempo actual para mayor aleatoriedad
    random_device rd;
    auto seed = rd() ^ static_cast<unsigned long>(chrono::high_resolution_clock::now().time_since_epoch().count());
    mt19937 gen(seed); // Semilla combinada
    uniform_int_distribution<> dis(min_value, max_value);
    
    for (size_t i = 0; i < count; ++i)
    {
        keys[i] = dis(gen);
    }

    return keys;
}

// Medir rendimiento de una estructura de datos con caché
template <typename MapType>
void benchmarkCacheWithBTreeCache(const string &name, MapType &cache, const vector<int> &insert_keys, const vector<int> &search_keys, vector<vector<string>> &results)
{
    cout << "Benchmarking " << name << "...\n";

    vector<string> row = {name};

    // Inserción
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < insert_keys.size(); ++i)
    {
        cache[insert_keys[i]] = i;
    }
    auto end = high_resolution_clock::now();
    auto insertion_time = duration_cast<milliseconds>(end - start).count();
    cout << "Tiempo de insercion: " << insertion_time << " ms\n";
    row.push_back(to_string(insertion_time));

    // Búsqueda con caché
    absl::btree_map<int, int> search_cache; // Caché para almacenar resultados de búsqueda
    size_t hits = 0;
    start = high_resolution_clock::now();
    for (size_t i = 0; i < search_keys.size(); ++i)
    {
        int key = search_keys[i];

        // Verificar si la clave ya está en la caché
        auto cache_it = search_cache.find(key);
        if (cache_it != search_cache.end())
        {
            ++hits; // La clave ya estaba en la caché
        }
        else
        {
            // Realizar la búsqueda en la estructura principal
            auto it = cache.find(key);
            if (it != cache.end())
            {
                ++hits;
                search_cache[key] = it->second; // Almacenar el resultado en la caché
            }
        }
    }
    end = high_resolution_clock::now();
    auto search_time = duration_cast<milliseconds>(end - start).count();
    cout << "Search time (with cache): " << search_time << " ms\n";
    row.push_back(to_string(search_time));

    // Tasa de aciertos
    double hit_rate = static_cast<double>(hits) / search_keys.size() * 100;
    cout << "Hit rate: " << hit_rate << "%\n";
    row.push_back(to_string(hit_rate));

    // Eliminación
    start = high_resolution_clock::now();
    for (size_t i = 0; i < insert_keys.size(); ++i)
    {
        cache.erase(insert_keys[i]);
    }
    end = high_resolution_clock::now();
    auto deletion_time = duration_cast<milliseconds>(end - start).count();
    cout << "Deletion time: " << deletion_time << " ms\n";
    row.push_back(to_string(deletion_time));

    results.push_back(row);
}

int main()
{
    // Configuración inicial
    const size_t num_keys = 100000; // Número de claves
    const int base_min_value = 1;  // Valor base mínimo para el rango
    const int base_max_value = 190000; // Valor base máximo para el rango

    // Generador de números aleatorios
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> range_offset_dis(0, 10000); // Desplazamiento aleatorio

    // Rango de inserción
    int range_offset_insert = range_offset_dis(gen);
    int min_value_insert = base_min_value + range_offset_insert;
    int max_value_insert = base_max_value + range_offset_insert;

    // Generar claves aleatorias para inserción
    vector<int> insert_keys = generateRandomKeys(num_keys, min_value_insert, max_value_insert);

    // Rango de búsqueda
    int range_offset_search = range_offset_dis(gen);
    int min_value_search = base_min_value + range_offset_search;
    int max_value_search = base_max_value + range_offset_search;

    // Generar claves aleatorias para búsqueda
    vector<int> search_keys = generateRandomKeys(num_keys, min_value_search, max_value_search);

    // Matriz de resultados
    vector<vector<string>> results;
    results.push_back({"Estructura", "Insercion (ms)", "Busqueda (ms)", "Tasa Acierto (%)", "Eliminacion (ms)"});

    // Benchmark para Boost Flat Map
    boost::container::flat_map<int, int> boost_cache;
    benchmarkCacheWithBTreeCache("Boost Flat Map", boost_cache, insert_keys, search_keys, results);

    // Benchmark para Google B-Tree Map (Abseil)
    absl::btree_map<int, int> google_cache;
    benchmarkCacheWithBTreeCache("Google B-Tree Map", google_cache, insert_keys, search_keys, results);

    // Mostrar resultados como tabla alineada
    cout << "\nCuadro Comparativo:\n";
    cout << left << setw(20) << "Estructura"
         << setw(20) << "Inserccion (ms)"
         << setw(20) << "Busqueda (ms)"
         << setw(20) << "Tasa Aciertos (%)"
         << setw(20) << "Eliminacion (ms)" << "\n";
    cout << string(100, '-') << "\n";

    for (const auto &row : results)
    {
        for (const auto &col : row)
        {
            cout << left << setw(20) << col;
        }
        cout << "\n";
    }

    return 0;
}