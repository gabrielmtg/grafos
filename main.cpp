#include "GrafoNaoDirigido.hpp"
#include "AlgoritmosA1.hpp"
#include <iostream>

int main() {
    std::string arquivo = "grafo.txt";

    GrafoNaoDirigido grafo = GrafoNaoDirigido(arquivo);

    std::cout << "===== TESTE BFS =====" << std::endl;
    buscaEmLargura(arquivo, 1); // começa no vértice 1

    std::cout << "\n===== TESTE CICLO EULERIANO =====" << std::endl;
    GrafoNaoDirigido g(arquivo);
    cicloEuleriano(g);

    std::cout << "\n===== TESTE DIJKSTRA =====" << std::endl;
    dijkstra(grafo, 1); // origem = vértice 1

    std::cout << "\n===== TESTE FLOYD-WARSHALL =====" << std::endl;
    floydWarshall(grafo);

    return 0;
}
