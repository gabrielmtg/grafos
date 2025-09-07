#include "GrafoNaoDirigido.hpp"
#include <iostream>
#include <queue>
#include <map>
#include <unordered_set>
#include <vector>

void buscaEmLargura(std::string grafoPath, int verticeInicial) {
       GrafoNaoDirigido grafo = GrafoNaoDirigido(grafoPath);
       
       std::map<int, std::vector<int>> verticesPorNivel; // n: vertices
       std::unordered_set<int> visitados;
       

       std::queue<std::pair<int, int>> fila; // (vertice, nivel)
       fila.push({verticeInicial, 0});
       visitados.insert(verticeInicial);

       while (!fila.empty()) {
              auto [vert, nivel] = fila.front();
              fila.pop();
              
              verticesPorNivel[nivel].push_back(vert);

              for (const auto& [vizinho, peso] : grafo.vizinhos(vert)) {
                     if (visitados.insert(vizinho).second) {
                            fila.push({vizinho, nivel + 1});
                     }
              }
       }

       for (auto& [nivel, vertices] : verticesPorNivel) {
              std::cout << nivel << ": ";
              for (int j = 0; j < vertices.size(); j++) {
                     std::cout << vertices[j];
                     if (j < vertices.size() -1) std::cout << ", ";
              }
              std::cout << "\n";
       }
}
