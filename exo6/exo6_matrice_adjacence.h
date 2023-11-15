//
// Created by franzozich on 15/11/23.
//

#include <vector>
#include <string>

#ifndef TP1_ALGORITHMIQUE_EXO6_MATRICE_ADJACENCE_H
#define TP1_ALGORITHMIQUE_EXO6_MATRICE_ADJACENCE_H

#endif //TP1_ALGORITHMIQUE_EXO6_MATRICE_ADJACENCE_H
void addEdge(int x, int y, int weight);
void initMatrix(std::vector<std::vector<int>> &matrix, int size);
void spanningTree(const std::string &filename);
void dijkstra();
void writePath(const std::string &pathName);
void exo6matrice();