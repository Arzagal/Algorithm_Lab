//
// Created by louis on 11/10/23.
//
#include <iostream>


void findXfrom1(int X){
    int temp = 1;
    int count=0;
    std::cout << "1";
    while(temp!=X && count <10000){
        if(X>temp){
            temp = temp *2;
            std::cout <<"*2";
        }
        else{
            temp = int(temp/3);
            std::cout <<"/3";
        }
        count++;
    }
    if(temp != X){
        std::cout << "\n no results found !\n";
    }
    else{
        std::cout << " = X\n We found a solution !\n";
    }
}
//int main(int argc, char * argv[]){
//    int X;
//    std::cout << "Welcome in the Exercice 1 program \n";
//    std::cout << "Please enter the goal number\n";
//    std::cin>>X;
//    findXfrom1(X);
//}