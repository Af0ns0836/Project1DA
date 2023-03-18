//
// Created by dias4 on 18/03/2023.
//
#include "setup.h"
#include "iostream"

using namespace std;

int main(){
    readstations();
    bool end = false;
    char option;
    while(!end){
        cout << "#############################" << endl;
        cout << "1.HELLO" << endl;
        cout << "Introduza a opcao ou q para terminar: ";
        cin >> option;
        if(option == 'q') end = true;
    }
    return 0;
}
