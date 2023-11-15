//
// Created by louis on 11/13/23.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "exo3.h"
// Cette fonction est la fonction principale, permettant de trouver dans une liste a de taille n la sous sequence
// la plus grande telle que la somme des elements est divisible par k
// La méthode decrite ci-dessous utilise la programmation dynamique : on utilise un tableau de taille n*k dans lequel la
// dimension de taille k représente le reste de la division par k. Lelement stocke dans la case (i,j) est la taille de la
// plus grande somme finissant par lelement i dont le reste de la division par k est j.
std::vector<int> getSousSeq(int a[], int n, int k){
    std::vector<std::vector<int>> array(
            n,
            std::vector<int>(k, 0)); // On crée le tableau que l'on va utiliser pour stocker les résultats des problemes intermédaires
    std::vector<int> indres; // La variable de retour, dans laquelle on stocke les indice du resultat (cf ex2)
    int res_max = 1; // La taille de la sous sequence resultat
    int act, ind_max; // On initialise des variables utilisee ci-dessius
    for(int i = 0; i<n; i++) { // On itere le long du tableau
        act = a[i]%k; // La valeur de la case que l'on regarde sur la liste dentree ramenée entre 0 et 4
        array[i][act] = 1; // On écrit par défaut dans la case correspondante un 1 (la liste ne comprends que lelement actuel, 1 seul element donc)
        for (int h = 0; h < k; h++) { // On itere sur lautre dimension du tableau (les restes
            int target = (h - act);
            while(target<0){target+=5;}
            target = target%k; // On calcule la case que l'on va regarder pour savoir si on peut ajouter lelement actuel a une somme precedente et avoir un reste h
            for (int j = 0; j < i; j++) { // On itere sur tous les resultats des problemes precedents
                if (array[j][target] + 1 > array[i][h] && array[j][target] != 0) { // Si la nouvelle suite trouvée est plus grande et que la suite precedente existe
                    array[i][h] = array[j][target] + 1; // On ajoute cette suite dans la case (i,h)
                }
            }
            if (array[i][0] > res_max) { // Si le resultat est la nouvelle plus grande suite divisible par k (reste 0)
                res_max = array[i][0];
                ind_max = i; // On recupere le resultat
            }
        }
    }
    int ligne_pre = 0;

    for(int m = 0; m < res_max; m++){
        indres.insert(indres.begin(), ind_max); // on ajoute le resultat au debut de la liste (on la remonte en sens inverse)

        int max_pre=0;
        int ind_pre = 0;
        ligne_pre = (ligne_pre-a[ind_max]); // on calcule la ligne sur laquelle on va regarder pour lelement precedent
        while(ligne_pre<0){ligne_pre+=5;}
        ligne_pre = ligne_pre%k;
        for(int p =0; p<ind_max; p++){
            if(array[p][ligne_pre]>max_pre){
                max_pre = array[p][ligne_pre]; // On va chercher la ligne la plus grande
                ind_pre = p;
            }
        }
        ind_max = ind_pre; // On pointe sur lelement precedent
    }
    return indres;
}



void ex3(){
    std::fstream input_file; // La gestion des fichiers dentree est sortie est la meme que ppur l'ex2
    input_file.open("INPDIVSEQ.TXT");
    int n, k;
    int a[100] ;
    char tempC[100];
    int h = 0;
    if(input_file.is_open()){
        std::string temp;
        std::getline(input_file, temp);
        std::stringstream temps(temp);
        std::string number;
        temps>>number;
        n = stoi(number);

        temps>>number;
        k = stoi(number);

        std::getline(input_file, temp);
        std::stringstream temps2(temp);
        while(temps2>>number && h<n) {
            a[h] = stoi(number);
            h++;
        }
    }
    input_file.close();
    std::vector<int> resultat = getSousSeq(a, n, k);
    int res_max = resultat.size();
    int somme = 0;
    std::ofstream output_file;
    output_file.open("OUTDIVOSEQ.TXT"); // On ouvre ou crée si il n'existe pas le fichier de résultat
    output_file << res_max; // On écrit sur la premiere ligne la taille du résultat
    output_file << "\n";
    for (k = 0; k < res_max; k++) {
        output_file << "a[";
        output_file << resultat[k];
        output_file << "] = ";
        output_file << a[resultat[k]];
        output_file << "\n"; //Simple mise en forme du résultat dans le
        somme += a[resultat[k]];
    }
    output_file<< "Sum = ";
    output_file<< somme;
    output_file.close();
    // Note : cela erait plus propre d'ecrire des fonctions de lecture et d'ecriture, mais cela fait peu de difference dans ce code
    return 0;
}