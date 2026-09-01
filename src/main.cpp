#include <iostream>
#include <fstream>

#include "../data/generador.hpp"
#include "colaCircular.hpp"
#include "listas.hpp"
#include "ratelimiter.hpp"

int main(){

    int C = 3;
    int T = 1000;
    int L = 3;

    generarCaso("data/caso1.txt", 5, 123);
    std::ifstream file("data/caso1.txt");

    if (!file.is_open()){
        std::cerr << "No se pudo abrir caso1.txt\n";
        return 1;
    }

    colaCircular buffer(C);
    listas colaLista;
    RateLimiter rate(T, L);

    int timestamp;
    int size;
    
    std::cout << "\n";
    std::cout << "caso1 \n";
    int contador = 0;

    while (file >> timestamp >> size && contador < 2){

        std::cout << "Timestamp: "
                  << timestamp << " ms\n";

        std::cout << "Size: "
                  << size << " bytes\n";

        if (!buffer.isFull() && rate.allow(timestamp)){
            buffer.enqueue(size);
            colaLista.enqueue(timestamp);

            std::cout << "ACEPTADO\n";
        }

        contador++;
    }

    std::cout << "Buffer: ";
    buffer.print();

    std::cout << "\n";
    std::cout << "caso 2\n";

    colaCircular bufferVacio(C);

    if (bufferVacio.isEmpty()){
        std::cout << "El buffer esta vacio\n";
    }
    else{
        std::cout << "El buffer NO esta vacio\n";
    }

    std::cout << "\n";
    std::cout << "Caso 3\n";

    colaCircular unPaquete(C);
    RateLimiter rateUnico(T, L);

    timestamp = 100;
    size = 500;

    if (!unPaquete.isFull() &&
        rateUnico.allow(timestamp)){
        unPaquete.enqueue(size);

        std::cout << "Paquete aceptado\n";
    }

    std::cout << "Buffer: ";
    unPaquete.print();

    std::cout << "\n";
    std::cout << "Caso 4\n";

    colaCircular bufferLleno(C);

    bufferLleno.enqueue(100);
    bufferLleno.enqueue(200);
    bufferLleno.enqueue(300);

    std::cout << "Buffer: ";
    bufferLleno.print();

    if (bufferLleno.isFull()){
        std::cout << "El buffer esta lleno\n";
    }

    if (!bufferLleno.enqueue(400)){
        std::cout << "Paquete adicional rechazado: "
                  << "buffer lleno\n";
    }

    std::cout << "\n";
    std::cout << "Caso 5\n";

    RateLimiter rateRafaga(T, L);

    int tiempos[] = {0, 100, 200, 300};

    for (int i = 0; i < 4; i++){
        if (rateRafaga.allow(tiempos[i])){
            std::cout << "t = "
                      << tiempos[i]
                      << " ms: ACEPTADO\n";
        }
        else{
            std::cout << "t = "
                      << tiempos[i]
                      << " ms: RECHAZADO - "
                      << "LIMITE DE TASA\n";
        }
    }

    std::cout << "\n";
    std::cout << "caso 6\n";

    colaCircular dequeueVacio(C);

    int valor;

    if (!dequeueVacio.dequeue(valor)){
        std::cout << "Dequeue rechazado: "
                  << "buffer vacio\n";
    }

    std::cout << "\n";
    std::cout << "caso 7\n";

    RateLimiter rateBorde(T, 1);

    if (rateBorde.allow(0)){
        std::cout << "t = 0 ms: ACEPTADO\n";
    }

    if (rateBorde.allow(T)){
        std::cout << "t = "
                  << T
                  << " ms: ACEPTADO\n";
    }
    else{
        std::cout << "t = "
                  << T
                  << " ms: RECHAZADO\n";
    }

    std::cout << "========================================\n";

    std::cout << "Buffer principal: ";
    buffer.print();

    std::cout << "Cola de timestamps: ";
    colaLista.print();

    std::cout << "Rate limiter: ";
    rate.printState();

    file.close();

    return 0;
}