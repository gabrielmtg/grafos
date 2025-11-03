#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <limits>
#include <fstream>
#include <sstream> // Para std::stringstream
#include <algorithm>

using Vizinho = std::pair<int, double>;

class GrafoDirigido {
private:
    int numVertices;
    int numArestas;
    std::unordered_map<int, std::list<Vizinho>> adj; // Lista de adjacência
    std::vector<std::string> rotulos; // Guarda os rótulos de cada vértice

public:
    GrafoDirigido(const std::string& nomeArquivo);
    ~GrafoDirigido();

    int qtdVertices() const;
    int qtdArestas() const;
    int grau(int v) const;
    std::string rotulo(int v) const;
    const std::list<Vizinho>& vizinhos(int v) const;
    bool haAresta(int u, int v) const;
    double peso(int u, int v) const;
    GrafoDirigido getTransposto() const;

private:
    void lerArquivo(const std::string& nomeArquivo);
};