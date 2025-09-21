#include "GrafoNaoDirigido.hpp"
#include <iostream>
#include <queue>
#include <map>
#include <unordered_set>
#include <vector>
#include <list>
#include <stack>

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
              for (size_t j = 0; j < vertices.size(); j++) {
                     std::cout << vertices[j];
                     if (j < vertices.size() -1) std::cout << ", ";
              }
              std::cout << "\n";
       }
}

/*void cicloEuleriano(GrafoNaoDirigido grafo) {
       int num_vertices = grafo.qtdVertices();
       std::vector<std::vector<int>> adj(num_vertices, std::vector(num_vertices,0));

       for (int i = 0; i < num_vertices; i++) {
              for (std::pair<int, double> v : grafo.vizinhos(i)) {
                   adj[i][v.first] = v.second;  
              }
       }

       std::vector<int> caminho, pilha;
       pilha.push_back(0);

       while (!pilha.empty()) {
              int u = pilha.back();
              int v = -1;
              for (int i = 0; i < num_vertices; i++) {
                     if (adj[u][i] != 0) {
                            v = i;
                            break;
                     }
              }
              if (v != -1) {
                     pilha.push_back(v);
                     adj[u][v] = adj[v][u] = 0;
              } else {
                     caminho.push_back(u);
                     pilha.pop_back();
              }
       }

       for (size_t i = 0; i < caminho.size(); i++) {
              std::cout << caminho[i] + 1; // +1 pq vértices no arquivo começam em 1
              if (i < caminho.size() - 1) std::cout << ",";
       }
       std::cout << std::endl;
}
*/

void cicloEuleriano(const GrafoNaoDirigido& grafo) {
    // 1. VERIFICAÇÃO DE CONDIÇÃO: Todos os vértices com arestas devem ter grau par.
    for (int i = 1; i <= grafo.qtdVertices(); ++i) {
        if (grafo.grau(i) > 0 && grafo.grau(i) % 2 != 0) {
            std::cout << 0 << std::endl;
            return; // Se algum vértice tem grau ímpar, não há ciclo euleriano.
        }
    }

    // 2. PREPARAÇÃO: Criar uma cópia local e modificável da lista de adjacência.
    // Usamos os métodos públicos de 'grafo' para construir nossa cópia.
    std::unordered_map<int, std::list<int>> adj_copia;
    for (int i = 1; i <= grafo.qtdVertices(); ++i) {
        // grafo.vizinhos(i) nos dá a lista de vizinhos que não podemos alterar.
        for (const Vizinho& vizinho : grafo.vizinhos(i)) {
            // Adicionamos o vizinho (sem o peso) à nossa lista local.
            adj_copia[i].push_back(vizinho.first);
        }
    }

    // 3. ALGORITMO DE HIERHOLZER
    std::stack<int> pilha;
    std::vector<int> ciclo;

    // Encontra um vértice inicial que tenha arestas
    int vertice_inicial = -1;
    for (int i = 1; i <= grafo.qtdVertices(); ++i) {
        if (grafo.grau(i) > 0) {
            vertice_inicial = i;
            break;
        }
    }

    // Se o grafo não tem arestas, o ciclo é trivial.
    if (vertice_inicial == -1) {
        std::cout << 1 << std::endl;
        // Nenhum vértice para imprimir.
        return;
    }

    pilha.push(vertice_inicial);

    while (!pilha.empty()) {
        int u = pilha.top();
        
        // Se o vértice u ainda tem arestas não visitadas em nossa cópia local.
        if (!adj_copia[u].empty()) {
            // Pega o próximo vizinho
            int v = adj_copia[u].front();
            pilha.push(v);

            // Remove a aresta (u, v) e (v, u) da nossa cópia local.
            adj_copia[u].pop_front();
            for (auto it = adj_copia[v].begin(); it != adj_copia[v].end(); ++it) {
                if (*it == u) {
                    adj_copia[v].erase(it);
                    break;
                }
            }
        } else {
            // Se u não tem mais arestas, ele faz parte do ciclo final.
            ciclo.push_back(u);
            pilha.pop();
        }
    }

    // O algoritmo produz o ciclo na ordem inversa.
    std::reverse(ciclo.begin(), ciclo.end());
    
    // 4. VERIFICAÇÃO FINAL E SAÍDA
    // Se o ciclo encontrado usou todas as arestas, seu tamanho será qtdArestas() + 1.
    // Esta é uma verificação importante para grafos desconexos.
    if (ciclo.size() == grafo.qtdArestas() + 1) {
        std::cout << 1 << std::endl;
        for (size_t i = 0; i < ciclo.size(); ++i) {
            std::cout << ciclo[i] << (i == ciclo.size() - 1 ? "" : ",");
        }
        std::cout << std::endl;
    } else {
        // O grafo tem todos os graus pares, mas não é conexo.
        std::cout << 0 << std::endl;
    }
}


void dijkstra(const GrafoNaoDirigido &grafo, int origem) {
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
