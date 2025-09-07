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

GrafoNaoDirigido::GrafoNaoDirigido(const std::string& nomeArquivo) {
    lerArquivo(nomeArquivo);
}

GrafoNaoDirigido::~GrafoNaoDirigido() {
    
}

int GrafoNaoDirigido::qtdVertices() const {
    return this->numVertices;
}

int GrafoNaoDirigido::qtdArestas() const {
    return this->numArestas;
}

int GrafoNaoDirigido::grau(int v) const {
    auto it = adj.find(v);
    if (it == adj.end()) {
        return 0;
    }

    return it->second.size();
}

std::string GrafoNaoDirigido::rotulo(int v) const {
    return rotulos.at(v - 1);
}

const std::list<Vizinho>& GrafoNaoDirigido::vizinhos(int v) const {
    auto it = adj.find(v);

    if (it == adj.end()) {
        static const std::list<Vizinho> listaVazia;
        return listaVazia;
    }

    return it->second;
}

bool GrafoNaoDirigido::haAresta(int u, int v) const {

    for (Vizinho vizinho : adj.at(u)) {
        if (vizinho.first == v) {
            return true;
        }
    }
    return false;
}

double GrafoNaoDirigido::peso(int u, int v) const {
    for (Vizinho vizinho : adj.at(u)) {
        if (vizinho.first == v) {
            return vizinho.second;
        }
    }
    return std::numeric_limits<double>::infinity();
}

void GrafoNaoDirigido::lerArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    std::string linha;

    //extrai o numero de vertices do texto
    std::getline(arquivo, linha);
    int pos = linha.find_last_of(' ');
    std::string nVerticesSTR = linha.substr(pos + 1);
    int nVertices = std::stoi(nVerticesSTR);

    this->numVertices = nVertices;
    this->numArestas = 0;

    for (int i = 0; i < nVertices; i++) {
        std::getline(arquivo, linha);
        int pos = linha.find_last_of(' ');
        std::string rotulo = linha.substr(pos + 1);
        this->rotulos.push_back(rotulo);
    }

    std::getline(arquivo, linha); //exclui a linha: *edge
    std::unordered_set<std::string> arestasAdicionadas; //para controlar se a aresta ja foi criada

    while (std::getline(arquivo, linha)) {
        int pos1 = linha.find_first_of(' ');
        int pos2 = linha.find_last_of(' ');

        int a = std::stoi(linha.substr(0, pos1));
        int b = std::stoi(linha.substr(pos1 + 1, pos2 - pos1 - 1));
        double peso = std::stod(linha.substr(pos2 + 1));

        std::string chaveAresta = std::to_string(std::min(a,b)) + "-" + std::to_string(std::max(a,b));

        auto resultadoInsercao = arestasAdicionadas.insert(chaveAresta);

        if (resultadoInsercao.second) {
            this->adj[a].push_back(Vizinho{b, peso});
            this->adj[b].push_back(Vizinho{a, peso});
            this->numArestas++;
        }
    }
}
