#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm> // Para std::sort
#include <numeric>   // Para std::iota
#include <iomanip>   // Para std::fixed e std::setprecision
#include "../grafo_nao_dirigido/GrafoNaoDirigido.hpp" // Usa a biblioteca de grafo não-dirigido

// Estrutura para representar uma aresta
struct Aresta {
    int u, v;
    double peso;

    // Comparador para ordenar arestas por peso
    bool operator<(const Aresta& outra) const {
        return peso < outra.peso;
    }
};

// Estrutura DSU (Disjoint Set Union) ou Union-Find
struct DSU {
    std::vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        std::iota(parent.begin(), parent.end(), 0); // Inicializa parent[i] = i
    }

    // Encontra o representante do conjunto de i (com compressão de caminho)
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    // Une os conjuntos de x e y
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_do_grafo>" << std::endl;
        return 1;
    }

    std::string nomeArquivo = argv[1];
    GrafoNaoDirigido g(nomeArquivo);

    std::vector<Aresta> arestas;
    int n = g.qtdVertices();

    // Coleta todas as arestas do grafo
    // Evita duplicatas (u,v) e (v,u) adicionando apenas se u < v
    for (int u = 1; u <= n; ++u) {
        for (const auto& vizinho : g.vizinhos(u)) {
            int v = vizinho.first;
            double peso = vizinho.second;
            if (u < v) {
                arestas.push_back({u, v, peso});
            }
        }
    }

    // Ordena as arestas por peso (base do Kruskal)
    std::sort(arestas.begin(), arestas.end());

    DSU dsu(n);
    double pesoTotal = 0.0;
    std::vector<std::string> arestasMST;

    // Algoritmo de Kruskal
    for (const auto& aresta : arestas) {
        if (dsu.find(aresta.u) != dsu.find(aresta.v)) {
            dsu.unite(aresta.u, aresta.v);
            pesoTotal += aresta.peso;
            // Formata a aresta como "u-v" [cite: 127]
            arestasMST.push_back(std::to_string(aresta.u) + "-" + std::to_string(aresta.v));
        }
    }

    // Imprime o somatório do peso [cite: 124, 126]
    std::cout << std::fixed << std::setprecision(1) << pesoTotal << std::endl;

    // Imprime as arestas da árvore [cite: 124, 127]
    for (size_t i = 0; i < arestasMST.size(); ++i) {
        std::cout << arestasMST[i];
        if (i < arestasMST.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    return 0;
}