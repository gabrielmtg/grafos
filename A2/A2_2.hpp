#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include "../grafo_dirigido/GrafoDirigido.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_do_grafo>" << std::endl;
        return 1;
    }

    std::string nomeArquivo = argv[1];
    GrafoDirigido g(nomeArquivo);

    // Mapa para armazenar os graus de entrada (in-degree) de cada vértice
    std::unordered_map<int, int> in_degree;
    for (int i = 1; i <= g.qtdVertices(); ++i) {
        in_degree[i] = 0; // Inicializa todos com 0
    }

    // Calcula o in-degree
    for (int u = 1; u <= g.qtdVertices(); ++u) {
        for (const auto& vizinho : g.vizinhos(u)) {
            in_degree[vizinho.first]++;
        }
    }

    // Fila para vértices com in-degree 0
    std::queue<int> fila;
    for (int i = 1; i <= g.qtdVertices(); ++i) {
        if (in_degree[i] == 0) {
            fila.push(i);
        }
    }

    std::vector<int> ordem_topologica;

    // Processo do Algoritmo de Kahn
    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();
        ordem_topologica.push_back(u);

        for (const auto& vizinho : g.vizinhos(u)) {
            int v = vizinho.first;
            in_degree[v]--;
            if (in_degree[v] == 0) {
                fila.push(v);
            }
        }
    }

    // Verifica se há ciclo (se a ordenação não incluiu todos os vértices)
    if (ordem_topologica.size() != (size_t)g.qtdVertices()) {
        std::cerr << "Erro: O grafo contém um ciclo, ordenação topológica não é possível." << std::endl;
        return 1;
    }

    // Imprime a ordem topológica usando os rótulos [cite: 121]
    for (size_t i = 0; i < ordem_topologica.size(); ++i) {
        std::cout << g.rotulo(ordem_topologica[i]);
        if (i < ordem_topologica.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    return 0;
}