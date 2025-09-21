#include "GrafoNaoDirigido.hpp"
#include "AlgoritmosA1.hpp"
#include <iostream>

int main() {
    GrafoNaoDirigido grafoBfs = GrafoNaoDirigido("grafos_A1/grafo_bfs.txt");
    GrafoNaoDirigido grafoEuleriano = GrafoNaoDirigido("grafos_A1/grafo_euleriano.txt");
    GrafoNaoDirigido grafoDijkstra = GrafoNaoDirigido("grafos_A1/grafo_dijkstra.txt");
    GrafoNaoDirigido grafoFloyMarshall = GrafoNaoDirigido("grafos_A1/grafo_floydWarshall.txt");
    
    std::cout << "===== TESTE BFS =====" << std::endl;
    buscaEmLargura("grafos_A1/grafo_bfs.txt", 1); // começa no vértice 1

    std::cout << "\n===== TESTE CICLO EULERIANO =====" << std::endl;
    GrafoNaoDirigido g(grafoEuleriano);
    cicloEuleriano(g);

    std::cout << "\n===== TESTE DIJKSTRA =====" << std::endl;
    dijkstra(grafoDijkstra, 1); // origem = vértice 1

    std::cout << "\n===== TESTE FLOYD-WARSHALL =====" << std::endl;
    floydWarshall(grafoFloyMarshall);

    return 0;
}
