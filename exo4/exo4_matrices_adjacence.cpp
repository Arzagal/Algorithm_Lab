#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include "exo4_matrices_adjacence.h"
std::vector<std::vector<int>> adj;
std::vector<std::vector<int>> span;
/*
 * Cette fonction ajoute une branche du graphe dans la matrice d'ajacence
 * */
void addEdge(int x, int y) {
    adj[x-1][y-1] = 1;
    adj[y-1][x-1] = 1;
}
/*
 * Ici nous initialisons la matrice d'ajacence avec des zeros a l'interieur
 * */
void initMatrix(std::vector<std::vector<int>>& matrix, int size) {
    matrix.resize(size, std::vector<int>(size, 0));
}
/*
 * Nous écrivons ici les valeurs des nodes contenues dans le .txt
 * dans la patrice d'ajacence
 * */
void spanningTree(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier input'" << filename << "': "
                  << strerror(errno) << std::endl;  // Include error details
        return;
    }

    int n, m;
    file >> n >> m;

    initMatrix(adj, n);
    initMatrix(span, n);
    //Lecture et ajout des branches du graphe ligne a ligne
    int x, y;
    while (m-- && file >> x >> y) {
        addEdge(x, y);
    }

    file.close();
}
/*
 * Nous utilisons la méthode de depth first search qui
 * produit automatiquement un arbre couvrant
 * */
void dfs(int start, std::vector<bool>& visited) {
    visited[start] = true;
    for (int i = 0; i < adj[start].size(); ++i) {
        if (adj[start][i] == 1 && !visited[i]) {
            span[start][i] = 1;
            dfs(i, visited);
        }
    }
}
/*
 * Nous écrivons le résultat dans le fichier de destination
 * */
void writeSpanningTree(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier output" << std::endl;
        return;
    }

    for (int i = 0; i < span.size(); ++i) {
        for (int j = 0; j < span[i].size(); ++j) {
            if (span[i][j] == 1) {
                file << i + 1 << " " << j + 1 << std::endl;
            }
        }
    }

    file.close();
}


int ex4_1() {


    spanningTree("../exo4/INPARBGRAPH.TXT");
    std::vector<bool> visited(adj.size(), false);
    dfs(1, visited);
    writeSpanningTree("../exo4/OUTARBGRAPH.TXT");

    return 0;
}