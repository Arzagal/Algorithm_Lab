//
// Created by louis on 11/15/23.
//
#include <iostream>
#include <vector>
#include <fstream>

#ifndef TP_ALGO_EXO4_LISTE_ADJACENCE_H
#define TP_ALGO_EXO4_LISTE_ADJACENCE_H

#endif //TP_ALGO_EXO4_LISTE_ADJACENCE_H
struct AdjList;
struct Node;
void spanningTree2(const std::string& filename);
void dfs2(int start, std::vector<bool>& visited, std::vector<AdjList>& myAdj);
void writeSpanningTree2(const std::string& filename, const std::vector<AdjList>& myAdj);
int ex4_2();