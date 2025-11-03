#include "GrafoDirigido.hpp"

GrafoDirigido::GrafoDirigido(const std::string& nomeArquivo) : numVertices(0), numArestas(0) {
    lerArquivo(nomeArquivo);
}

GrafoDirigido::~GrafoDirigido() {}

void GrafoDirigido::lerArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return;
    }

    std::string linha;
    std::getline(arquivo, linha);
    std::stringstream ss(linha);
    std::string token;
    
    ss >> token >> this->numVertices;
    this->rotulos.resize(this->numVertices + 1);

    for (int i = 1; i <= this->numVertices; ++i) {
        std::getline(arquivo, linha);
        ss.clear();
        ss.str(linha);
        int indice;
        std::string rotulo_str;
        ss >> indice;
        std::getline(ss >> std::ws, rotulo_str); 
        this->rotulos[indice] = rotulo_str;
    }

    while (std::getline(arquivo, linha) && linha.find("*arcs") == std::string::npos) {}

    while (std::getline(arquivo, linha)) {
        ss.clear();
        ss.str(linha);
        int u, v;
        double peso = 1.0;
        if (ss >> u >> v) {
            ss >> peso;
            this->adj[u].push_back({v, peso});
            this->numArestas++;
        }
    }

    arquivo.close();
}

int GrafoDirigido::qtdVertices() const {
    return this->numVertices;
}

int GrafoDirigido::qtdArestas() const {
    return this->numArestas;
}

int GrafoDirigido::grau(int v) const {
    return this->adj.count(v) ? this->adj.at(v).size() : 0;
}

std::string GrafoDirigido::rotulo(int v) const {
    if (v >= 1 && v <= this->numVertices) {
        return this->rotulos[v];
    }
    return "";
}

const std::list<Vizinho>& GrafoDirigido::vizinhos(int v) const {
    static const std::list<Vizinho> listaVazia;
    if (this->adj.count(v)) {
        return this->adj.at(v);
    }
    return listaVazia;
}

bool GrafoDirigido::haAresta(int u, int v) const {
    if (this->adj.count(u)) {
        for (const auto& vizinho : this->adj.at(u)) {
            if (vizinho.first == v) {
                return true;
            }
        }
    }
    return false;
}

double GrafoDirigido::peso(int u, int v) const {
    if (this->adj.count(u)) {
        for (const auto& vizinho : this->adj.at(u)) {
            if (vizinho.first == v) {
                return vizinho.second;
            }
        }
    }
    return std::numeric_limits<double>::infinity();
}

GrafoDirigido GrafoDirigido::getTransposto() const {
    GrafoDirigido gT("");
    gT.numVertices = this->numVertices;
    gT.rotulos = this->rotulos;

    for (int u = 1; u <= this->numVertices; ++u) {
        if (this->adj.count(u)) {
            for (const auto& vizinho : this->adj.at(u)) {
                int v = vizinho.first;
                double p = vizinho.second;
                gT.adj[v].push_back({u, p});
                gT.numArestas++;
            }
        }
    }
    return gT;
}