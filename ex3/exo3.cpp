//
// Created by louis on 11/13/23.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

std::vector<int> getSousSeq(int a[], int n, int k){
    std::vector<std::vector<int>> array(
            n,
            std::vector<int>(k, 0));
    std::vector<int> indres;
    int res_max = 1;
    int act, ind_max;
    for(int i = 0; i<n; i++) {
        act = a[i]%k;
        array[i][act] = 1;
        for (int h = 0; h < k; h++) {
            int target = (h - act);
            while(target<0){target+=5;}
            target = target%k;
            for (int j = 0; j < i; j++) {
                if (array[j][target] + 1 > array[i][h] && array[j][target] != 0) {
                    array[i][h] = array[j][target] + 1;
                }
            }
            if (array[i][0] > res_max) {
                res_max = array[i][0];
                ind_max = i;
            }
        }
    }
    int ligne_pre = 0;

    for(int m = 0; m < res_max; m++){
        indres.insert(indres.begin(), ind_max);

        int max_pre=0;
        int ind_pre = 0;
        ligne_pre = (ligne_pre-a[ind_max]);
        while(ligne_pre<0){ligne_pre+=5;}
        ligne_pre = ligne_pre%k;
        for(int p =0; p<ind_max; p++){
            if(array[p][ligne_pre]>max_pre){
                max_pre = array[p][ligne_pre];
                ind_pre = p;
            }
        }
        ind_max = ind_pre;
    }
    return indres;
}



int main(){
    std::fstream input_file;
    input_file.open("../ex3/INPMONOSEQ.TXT");
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
    output_file.open("../ex3/OUTMONOSEQ.TXT"); // On ouvre ou crée si il n'existe pas le fichier de résultat
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
    return 0;
}