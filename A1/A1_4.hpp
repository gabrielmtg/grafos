#include "../grafo_nao_dirigido/GrafoNaoDirigido.hpp"
#include <vector>

void dijkstra(std::string arquivo, int origem) {
        GrafoNaoDirigido grafo = GrafoNaoDirigido(arquivo);
        int n = grafo.qtdVertices();
        std::vector<double> dist(n, std::numeric_limits<double>::infinity());
        std::vector<int> pai(n, -1);
        std::vector<bool> visitado(n, false);

        dist[origem - 1] = 0;
        
        for (int i = 0; i < n; i++) {
            // Encontra o vértice não visitado com a menor distância
            int u = -1;
            for (int j = 0; j < n; j++) {
                if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }
            if (u == -1 || dist[u] == std::numeric_limits<double>::infinity()) {
                break; // Todos os vértices alcançáveis foram visitados
            }
            visitado[u] = true;
            // Relaxa as arestas a partir de u
            // <-- CORREÇÃO 1: Usar u+1 para obter os vizinhos do vértice correto
            for (const Vizinho& v : grafo.vizinhos(u + 1)) {
                int id_vizinho = v.first;
                double peso = v.second;
                // <-- CORREÇÃO 2: Usar id_vizinho-1 para acessar os vetores
                if (dist[id_vizinho - 1] > dist[u] + peso) {
                    dist[id_vizinho - 1] = dist[u] + peso;
                    pai[id_vizinho - 1] = u;
                }
            }
        }
        // Saída no formato pedido (seu código de impressão já estava quase perfeito)
        for (int i = 0; i < n; i++) {
            std::cout << i + 1 << ": ";
            std::vector<int> caminho;
            for (int v_idx = i; v_idx != -1; v_idx = pai[v_idx]) {
                caminho.push_back(v_idx + 1);
            }
            std::reverse(caminho.begin(), caminho.end());
            for (size_t j = 0; j < caminho.size(); j++) {
                std::cout << caminho[j] << (j < caminho.size() - 1 ? "," : "");
            }
            std::cout << "; d=";
            if (dist[i] == std::numeric_limits<double>::infinity()) {
                std::cout << "infinito";
            } else {
                std::cout << dist[i];
            }
            std::cout << std::endl;
        }
}  