//
// Created by louis on 11/10/23.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


// Cette partie correspon au 2e exercice, se referer au sujet fourni pour plus d'explications sur l'objectif

// Fonction principale de l'exercice, qui a partir de la liste en entrée a de taille n trouve la séquence croissante la
// plus grande possible
std::vector<int> findsousseq(int n, int a[]) {
    std::vector<std::vector<int> > array(
            n,
            std::vector<int>(2, 1)); /*cette variable est le tableau qui va nous servir a résoudre l'exercice
    Le tableau array est un tableau de taille n*n. Pour remplir la colonne j, on teste si l'element j de a (lentrée)
    est supérieur a l'élement i de cette meme liste. si c'est le cas, on écrit alors à la ligne i la taille de la suite
    la plus grande prenant ce chemin, c'est à dire le plus grand element de la colonne i plus 1.
    Note : cette version n'est  pas optimale : jaurais du fairre un tableau de taille n*2, et stocker a la collone i
    la taille maximale de la suite finissant par lelement i et l'indice de l'element precedent.
    */
    std::vector<int> res; //Variable qui servira a stocker le resultat
    std::vector<int> vecind; //Variable qui stock les indices des elements de la suite, on lutilisera pour remplir le resultat
    int ind;
    int i,j,k;
    int res_max = 1; // taille du résultat
    for (i = 0; i < n; i++) { // On résoud tous les problemes de taille inférieur à n
        for (j = 0; j < i; j++) { //On eplore la liste des résultats deja calculés
            if (a[i] > a[j]) { //Si lelement actuel est supérieur a l'un des éléments précédent de la liste
                if (array[j][1] +1 > array[i][1]) { // Si cela donne une liste plus grande
                    array[i][1] = array[j][1] + 1; //On remplace l'élément par le nouveau
                    array[i][2] = j; //On note l'indice de l'élément
                }
            }
            if (array[i][1]>res_max){ // Si le résultat est la nouvelle plus grande liste possible
                res_max = array[i][1]; //On stocke la taille du résultat
                ind = i; // On stocke l'indice de la derniere valeur de la liste, pour pouvoir remonter
            }
        }
    }

    std::ofstream output_file;
    output_file.open("../ex2/OUTMONOSEQ.TXT"); // On ouvre ou crée si il n'existe pas le fichier de résultat
    output_file << res_max; // On écrit sur la premiere ligne la taille du résultat
    output_file << "\n";
    //std::cout << res_max; // Ligne de vérification
    for (k = 0; k < res_max; k++) { //On construit les vecteurs résulats en remontant les indices
        vecind.insert(vecind.begin(),ind);
        res.insert(res.begin(), a[ind]);
        ind = array[ind][2];
    }
    for (k = 0; k < res_max; k++) {
        output_file << "a[";
        output_file << vecind[k];
        output_file << "] = ";
        output_file << res[k];
        output_file << "\n"; //Simple mise en forme du résultat dans le
    }
    output_file.close();
    return res;
}

int main(){
    std::fstream input_file;
    input_file.open("../ex2/INPMONOSEQ.TXT");
    int n;
    int a[100] ;
    char tempC[100];
    int h = 0;
    if(input_file.is_open()){
        std::string temp;
        std::getline(input_file, temp);
        n = stoi(temp);

        std::getline(input_file, temp);
        std::stringstream temps(temp);
        std::string number;
        while(temps>>number && h<n) {
            a[h] = stoi(number);
            h++;
        }
    }
    input_file.close();
    std::vector<int> resultat = findsousseq(n, a);
    return 0;
}