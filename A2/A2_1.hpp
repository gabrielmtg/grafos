#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include "../grafo_dirigido/GrafoDirigido.hpp"

// Helper: DFS para o primeiro passo do Kosaraju (preencher a pilha de ordem)
void dfs_passo1(int u, const GrafoDirigido& g, std::unordered_set<int>& visitados, std::stack<int>& pilha) {
    visitados.insert(u);
    for (const auto& vizinho : g.vizinhos(u)) {
        int v = vizinho.first;
        if (visitados.find(v) == visitados.end()) {
            dfs_passo1(v, g, visitados, pilha);
        }
    }
    pilha.push(u); // Adiciona à pilha após visitar todos os vizinhos
}

// Helper: DFS para o segundo passo do Kosaraju (no grafo transposto)
void dfs_passo2(int u, const GrafoDirigido& gT, std::unordered_set<int>& visitados, std::list<int>& componente) {
    visitados.insert(u);
    componente.push_back(u);
    for (const auto& vizinho : gT.vizinhos(u)) {
        int v = vizinho.first;
        if (visitados.find(v) == visitados.end()) {
            dfs_passo2(v, gT, visitados, componente);
        }
    }
}

int main(int argc, char* argv[]) {
    // Verifica se o nome do arquivo foi passado como argumento [cite: 110]
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_do_grafo>" << std::endl;
        return 1;
    }

    std::string nomeArquivo = argv[1];
    GrafoDirigido g(nomeArquivo);

    std::stack<int> pilhaOrdem;
    std::unordered_set<int> visitados;

    // Passo 1: Executar DFS no grafo original (G) para preencher a pilha
    for (int i = 1; i <= g.qtdVertices(); ++i) {
        if (visitados.find(i) == visitados.end()) {
            dfs_passo1(i, g, visitados, pilhaOrdem);
        }
    }

    // Passo 2: Obter o grafo transposto (G^T)
    GrafoDirigido gT = g.getTransposto();

    visitados.clear(); // Limpa o conjunto de visitados para o segundo DFS

    // Passo 3: Processar os vértices na ordem da pilha no grafo transposto
    while (!pilhaOrdem.empty()) {
        int v = pilhaOrdem.top();
        pilhaOrdem.pop();

        if (visitados.find(v) == visitados.end()) {
            std::list<int> scc;
            dfs_passo2(v, gT, visitados, scc);

            // Imprimir a componente fortemente conexa no formato "3,4,5" [cite: 118]
            for (auto it = scc.begin(); it != scc.end(); ++it) {
                std::cout << *it;
                if (std::next(it) != scc.end()) {
                    std::cout << ",";
                }
            }
            std::cout << std::endl;
        }
    }

    return 0;
}