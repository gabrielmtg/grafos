#include "../GrafoNaoDirigido.hpp"
#include <vector>

void floydWarshall(const GrafoNaoDirigido& grafo) {
    int n = grafo.qtdVertices();
    if (n == 0) {
        return; // Grafo vazio, não faz nada.
    }

    // Matriz de distâncias inicializada com infinito
    std::vector<std::vector<double>> dist(n, std::vector<double>(n, std::numeric_limits<double>::infinity()));

    // --- CORREÇÃO NA INICIALIZAÇÃO ---
    // Itera por cada vértice do grafo usando índices de 0 a n-1
    for (int i = 0; i < n; ++i) {
        // 1. A distância de um vértice para si mesmo é 0.
        dist[i][i] = 0;

        // 2. Para cada vizinho, define a distância inicial como o peso da aresta.
        // CORREÇÃO: Chama vizinhos() com o rótulo do vértice (i + 1)
        for (const Vizinho& vizinho : grafo.vizinhos(i + 1)) {
            int j = vizinho.first;  // Rótulo do vizinho (ex: 1, 2, 3, 4)
            double peso = vizinho.second;

            // CORREÇÃO: Usa o índice correto (j - 1) para acessar a matriz
            if (peso < dist[i][j - 1]) {
                dist[i][j - 1] = peso;
            }
        }
    }

    // Algoritmo principal de Floyd-Warshall (o seu já estava correto)
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // Checa se os caminhos intermediários não são infinitos
                if (dist[i][k] != std::numeric_limits<double>::infinity() &&
                    dist[k][j] != std::numeric_limits<double>::infinity())
                {
                    // Se o caminho passando por k for menor, atualiza a distância
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    // Saída no formato solicitado pelo enunciado
    for (int i = 0; i < n; ++i) {
        std::cout << i + 1 << ":";
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == std::numeric_limits<double>::infinity()) {
                std::cout << "INF";
            } else {
                std::cout << dist[i][j];
            }
            if (j < n - 1) {
                std::cout << ",";
            }
        }
        std::cout << std::endl;
    }
}
