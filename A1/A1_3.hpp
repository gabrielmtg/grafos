#include "../GrafoNaoDirigido.hpp"
#include <stack>
#include <vector>

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