//
// Created by louis on 11/15/23.
//
#include <iostream>
#include <vector>
#include <fstream>

#ifndef TP_ALGO_EXO5_LISTES_H
#define TP_ALGO_EXO5_LISTES_H

#endif //TP_ALGO_EXO5_LISTES_H

struct Node ;
struct AdjList ;
void spanningTree5List(const std::string& filename);
void dfs5List(int start, std::vector<bool>& visited, int numero) ;
void isConnexList(std::vector<bool> visited, int numero);
void writeSpanningTree5List(const std::string& filename);
int ex5_2() ;