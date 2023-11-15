//
// Created by louis on 11/15/23.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

#ifndef TP_ALGO_EXO4_MATRICES_ADJACENCE_H
#define TP_ALGO_EXO4_MATRICES_ADJACENCE_H

#endif //TP_ALGO_EXO4_MATRICES_ADJACENCE_H
void addEdge(int x, int y);
void initMatrix(std::vector<std::vector<int>>& matrix, int size);
void spanningTree(const std::string& filename);
void dfs(int start, std::vector<bool>& visited);
void writeSpanningTree(const std::string& filename);
int ex4_1();