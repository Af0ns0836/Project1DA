//
// Created by afonso on 21-03-2023.
//

#include <cstring>
#include "Menu.h"
#include "Graph.h"
#include "TrainNetwork.h"

void menu(TrainNetwork trainNetwork){
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
            menu1(trainNetwork);
        }
        else if(option == '2'){
            menu2(trainNetwork);
        }
        else if(option == '3'){
            menu3(trainNetwork);
        }
    }
}

void menu1(TrainNetwork tN){
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
        else if(option == '2') {
            //meter as funcoes respetivas e isso

        }
        else if (option == '3'){
            int k = 0;
            cout << "Enter how many stations do you want to see: ";
            cin >> k;
            tN.SortStations(k);
        }
        //meter as funcoes respetivas e isso

    }
}

void menu2(TrainNetwork tN){
//meter as funcoes respetivas e isso

}

void menu3(TrainNetwork tN){
//meter as funcoes respetivas e isso

    bool end = false;
    char option;
    while(!end) {
        cout << "#############################" << endl;
        cout << "#           Menu 3          #" << endl;
        cout << "#############################" << endl;
        cout
                << "1.Maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity"
                << endl;
        cout << "2.Stations that are most affected by each segment fail" << endl;
        cout << "Enter the respective number or q to return to the main menu: ";
        cin >> option;
        if (option == 'q') end = true;
        else if (option == '1') {
            string source, sink;
            int s, t;
            cout << "Source: ";
            cin >> source;
            cout << "Sink: ";
            cin >> sink;
            for (auto e: tN.getGraph()->stations_) {
                if (source == e.second) {
                    s = e.first;
                }
                if (sink == e.second) {
                    t = e.first;
                }
            }
            cout << "Max flow = " << tN.getGraph()->maxFlow(s, t) << endl;
            return;

        } else if (option == '2') {
            //meter as funcoes respetivas e isso

        }
    }
}