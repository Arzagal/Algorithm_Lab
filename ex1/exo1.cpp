//
// Created by louis on 11/10/23.
//
#include <iostream>
#include <vector>
#include "exo1.h"
// On utilise l'algorithme de syracuse
void findXfrom1(int X) {
    int temp = X; // On part du resultat
    std::cout << "1";
    std::vector<bool> res;
    while (temp != 1) { //On itere tant que l'on a aps atteint 1, le resultat voulu
        if (temp % 2 == 0) { // On divise par 2 si c'est pair
            temp = temp / 2;
            res.push_back(true);
        } else {
            temp = temp * 3 + 1; // Sinon
            res.push_back(false);
        }
    }
    for (int i = res.size()-1; i>=0; i--){ // On reconstruit le resultat a afficher a partir des valeurs stockées
        if (res[i]) {
            std::cout << " *2";
        } else {
            std::cout << " /3";
        }
    }
    std::cout << "  = X\n";
    std::cout << "Goodbye Syracuse \n";
}
void ex1(){
    int X;
    std::cout << "Welcome in the Exercice 1 program \n";
    std::cout << "Please enter the goal number\n";
    std::cin>>X;
    findXfrom1(X);
}