//
// Created by afonso on 21-03-2023.
//

#include "Menu.h"

void menu(){
    bool end = false;
    char option;
    while(!end){
        cout << "#############################" << endl;
        cout << "#         MAIN MENU         #" << endl;
        cout << "#############################" << endl;
        cout << "1.Basic Service Metrics" << endl;
        cout << "2.Operation Cost Optimization" << endl;
        cout << "3.Reliability and Sensitivity to Line Failures" << endl;
        cout << "Enter the respective number or q to terminate the program: ";
        cin >> option;
        if(option == 'q') end = true;
        else if(option == '1'){
            menu1();
        }
        else if(option == '2'){
            menu2();
        }
        else if(option == '3'){
            menu3();
        }
    }
}

void menu1(){
    bool end = false;
    char option;
    while(!end){
        cout << "#############################" << endl;
        cout << "#           Menu 1          #" << endl;
        cout << "#############################" << endl;
        cout << "1.Number of trains between two specific stations" << endl;
        cout << "2.Stations that require the most amount of trains" << endl;
        cout << "3.Top-k municipalities and distritcs that are assigned larged budgets" << endl;
        cout << "4.Maximum number of trains that can simultaneously arrive at a given station" << endl;
        cout << "Enter the respective number or q to return to the main menu: ";
        cin >> option;
        if(option == 'q') end = true;
        else if(option == '1'){
            //meter as funcoes respetivas e isso
        }
        else if(option == '2'){
            //meter as funcoes respetivas e isso
        }
        else if (option == '3'){}
        //meter as funcoes respetivas e isso

    }
}

void menu2(){
//meter as funcoes respetivas e isso
}

void menu3(){
//meter as funcoes respetivas e isso
}