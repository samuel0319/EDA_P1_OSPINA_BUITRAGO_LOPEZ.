#include "generador.hpp"

#include <iostream>
#include <fstream>
#include <cstdlib>

void generarCaso(const char *archivo, int cantidad, int seed)
{
    std::ofstream file(archivo);

    if (!file.is_open())
    {
        std::cout << "No se pudo crear el archivo: "
                  << archivo << "\n";
        return;
    }

    std::srand(seed);

    int timestamp = 0;
    int size;

    for (int i = 0; i < cantidad; i++)
    {
        timestamp += 50 + std::rand() % 251;
        size = 100 + std::rand() % 901;

        file << timestamp << " "
             << size << "\n";
    }

    file.close();

    std::cout << "Datos generados en: "
              << archivo << "\n";
}