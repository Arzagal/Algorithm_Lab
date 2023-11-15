//
// Created by louis on 11/15/23.
//
#include <iostream>
#include <vector>
#include <fstream>
#include "exo5_listes.h"



struct Node {
    int vertex;
    Node* next;

    Node(int v) : vertex(v), next(nullptr) {}
};

struct AdjList {
    Node* head;

    AdjList() : head(nullptr) {}
    void addEdge2(int v) {
        Node* newNode = new Node(v);
        newNode->next = head;
        head = newNode;
    }
};

std::vector<AdjList> listAdj5;
std::vector<std::vector<int>> sousGrapheList(0);
void spanningTree5List(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    int n, m;
    file >> n >> m;

    listAdj5.resize(n);

    int x, y;
    while (m-- && file >> x >> y) {
        listAdj5[x - 1].addEdge2(y - 1); // Adjust for 0-based indexing
        listAdj5[y - 1].addEdge2(x - 1);
    }

    file.close();
}

void dfs5List(int start, std::vector<bool>& visited, int numero) {
    visited[start] = true;
    sousGrapheList[numero].push_back(start+1);
    for (Node* curr = listAdj5[start].head; curr != nullptr; curr = curr->next) {
        if (!visited[curr->vertex]) {
            dfs5List(curr->vertex, visited,  numero);
        }
    }
}

void isConnexList(std::vector<bool> visited, int numero){
    int start = 0;
    while(visited[start] && start<visited.size()){ // On ragrde dans la liste visited si il reste des sommets non visites
        start++;
    }
    if(start<visited.size()){ // Si des sommets sont non visites, on cree et remplit un nouveau sous graphe connexe
        std::vector<int> tempGr(0);
        sousGrapheList.push_back(tempGr);
        dfs5List(start, visited,  numero); // On utilise a noveau de depth first search
        numero++; // On passe au sous graphe suivant
        isConnexList(visited,  numero); // on reappelle la fonction jusqua ne plus avoir de sommets non visites
    }
}

void writeSpanningTree5List(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    int taille_res = sousGrapheList.size();
    if(1 == taille_res){
        file << "Le graphe est coonnexe" << std::endl;
    }
    else{
        file << taille_res << std::endl;
        for(int h = 0; h<taille_res; h++){
            file << "Composante connexe " << h+1 << std::endl;
            for(int g : sousGrapheList[h]){
                file << g  << " ";
            }
            file << std::endl;
        }
    }
    file.close();
}

int ex5_2() {

    int numero = 0;
    spanningTree5List("../ex5/INPCONGRAPH.TXT");
    std::vector<bool> visited2(listAdj5.size(), false);
    isConnexList(visited2, numero);
    writeSpanningTree5List("../ex5/OUTCONGRAPH.TXT");

    return 0;
}
