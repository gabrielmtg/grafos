#include "../grafo_nao_dirigido/GrafoNaoDirigido.hpp"
#include "A1_2.hpp"
#include "A1_3.hpp"
#include "A1_4.hpp"
#include "A1_5.hpp"
#include <iostream>

int main() {
    GrafoNaoDirigido grafoBfs = GrafoNaoDirigido("../grafos_A1/grafo_bfs.txt");
    GrafoNaoDirigido grafoEuleriano = GrafoNaoDirigido("../grafos_A1/grafo_euleriano.txt");
    GrafoNaoDirigido grafoDijkstra = GrafoNaoDirigido("../grafos_A1/grafo_dijkstra.txt");
    GrafoNaoDirigido grafoFloyMarshall = GrafoNaoDirigido("../grafos_A1/grafo_floydWarshall.txt");
    
    std::cout << "===== TESTE BFS =====" << std::endl;
    buscaEmLargura("../grafos_A1/grafo_bfs.txt", 1); // começa no vértice 1

    std::cout << "\n===== TESTE CICLO EULERIANO =====" << std::endl;
    GrafoNaoDirigido g(grafoEuleriano);
    cicloEuleriano(g);

    std::cout << "\n===== TESTE DIJKSTRA =====" << std::endl;
    dijkstra("../grafos_A1/grafo_dijkstra.txt", 1); // origem = vértice 1

    std::cout << "\n===== TESTE FLOYD-WARSHALL =====" << std::endl;
    floydWarshall("../grafos_A1/grafo_floydWarshall.txt");

    return 0;
}
