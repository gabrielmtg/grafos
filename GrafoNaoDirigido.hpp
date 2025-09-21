#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <fstream>
#include <algorithm>


//define o vizinho e o peso da aresta
using Vizinho = std::pair<int, double>;

class GrafoNaoDirigido {
private:
    int numVertices;
    int numArestas;
    std::unordered_map<int,std::list<Vizinho>> adj; //cada posicao x da lista possui uma lista de vizinhos do vertice x
    std::vector<std::string> rotulos; //guarda os rotulos de cada vertice

public:
    GrafoNaoDirigido(const std::string& nomeArquivo);
    ~GrafoNaoDirigido();

    int qtdVertices() const;
    int qtdArestas() const;
    int grau(int v) const;
    std::string rotulo(int v) const;
    const std::list<Vizinho>& vizinhos(int v) const;
    bool haAresta(int u,int v) const;
    double peso(int u,int v) const;

private:
    void lerArquivo(const std::string& nomeArquivo);
};