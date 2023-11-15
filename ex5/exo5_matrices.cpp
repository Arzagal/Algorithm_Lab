//
// Created by louis on 11/15/23.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include "exo5_matrices.h"

std::vector<std::vector<int>> adj5;
std::vector<std::vector<int>> sousGraphe(0);
/*
 * Cette fonction ajoute une branche du graphe dans la matrice d'ajacence
 * */
void addEdge5(int x, int y) {
    adj5[x-1][y-1] = 1;
    adj5[y-1][x-1] = 1;
}
/*
 * Ici nous initialisons la matrice d'ajacence avec des zeros a l'interieur
 * */
void initMatrix5(std::vector<std::vector<int>>& matrix, int size) {
    matrix.resize(size, std::vector<int>(size, 0));
}
/*
 * Nous écrivons ici les valeurs des nodes contenues dans le .txt
 * dans la patrice d'ajacence
 * */
void spanningTree5(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier output'" << filename << "': "
                  << strerror(errno) << std::endl;  // Include error details
        return;
    }

    int n, m;
    file >> n >> m;

    initMatrix5(adj5, n);
    //Lecture et ajout des branches du graphe ligne a ligne
    int x, y;
    while (m-- && file >> x >> y) {
        addEdge5(x, y);
    }

    file.close();
}

/* Nous utilisons la méthode de depth first search qui
        * produit automatiquement un arbre couvrant
* */
void dfs5(int start, std::vector<bool>& visited, int numero) {
    visited[start] = true;
    sousGraphe[numero].push_back(start+1); // La difference avec lexercice 4 : on note le noeud par lequel on vient de passer
    for (int i = 0; i < adj5[start].size(); ++i) {
        if (adj5[start][i] == 1 && !visited[i]) {
            dfs5(i, visited, numero);
        }
    }
}

void isConnex(std::vector<bool> visited, int numero){
    int start = 0;
    while(visited[start] && start<visited.size()){ // On ragrde dans la liste visited si il reste des sommets non visites
        start++;
    }
    if(start<visited.size()){ // Si des sommets sont non visites, on cree et remplit un nouveau sous graphe connexe
        std::vector<int> tempGr(0);
        sousGraphe.push_back(tempGr);
        dfs5(start, visited, numero); // On utilise a noveau de depth first search
        numero++; // On passe au sous graphe suivant
        isConnex(visited,  numero); // on reappelle la fonction jusqua ne plus avoir de sommets non visites
    }


}

void writeSpanningTree5(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier output" << std::endl;
        return;
    }

    int taille_res = sousGraphe.size();
    if(1 == taille_res){
        file << "Le graphe est coonnexe" << std::endl;
    }
    else{
        file << taille_res << std::endl;
        for(int h = 0; h<taille_res; h++){
            file << "Composante connexe " << h+1 << std::endl;
            for(int g : sousGraphe[h]){
                file << g  << " ";
            }
            file << std::endl;
        }
    }
    file.close();
}

int ex5_1() {
    spanningTree5("../ex5/INPCONGRAPH.TXT");
    std::vector<bool> visited(adj5.size(), false);
    int numero = 0;
    isConnex(visited, numero);
    writeSpanningTree5("../ex5/OUTCONGRAPH.TXT");

    return 0;
}