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
        cout << "Enter q to terminate the program or to return to a previous menu: ";
        cout << "Enter the respective number: ";
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
        cout << "1.Max number of trains between two specific stations" << endl;
        cout << "2.Stations that require the most amount of trains" << endl;
        cout << "3.Top-k municipalities and districts that are assigned large budgets" << endl;
        cout << "4.Maximum number of trains that can simultaneously arrive at a given station" << endl;
        cout << "Enter the respective number: ";
        cin >> option;
        if(option == 'q') end = true;
        else if(option == '1'){
            string source, sink;
            int s, t;
            cout << "Source: ";
            cin.ignore(); getline(cin, source, '\n');
            cout << "Destination: ";
            getline(cin, sink, '\n');
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

        }
        else if(option == '2') {
            ///Function that computes maximum num of trains between all pairs of stations | Time complexity: O(V^3E^2)
            vector<pair<Vertex*,Vertex*>> sts;
            vector<int> capacities;
            int max_trains = tN.getGraph()->getVertexSet()[0]->getAdj()[0]->getWeight();
            for(int i = 0; i < tN.getGraph()->getNumVertex(); i++){
                for(int j = i+1; j < tN.getGraph()->getNumVertex(); j++){
                    int cap = tN.getGraph()->maxFlow(tN.getGraph()->getVertexSet()[i]->getId(), tN.getGraph()->getVertexSet()[j]->getId());
                    if(cap >= max_trains){
                        max_trains = cap;
                        pair<Vertex*,Vertex*> p(tN.getGraph()->getVertexSet()[i],tN.getGraph()->getVertexSet()[j]);
                        sts.push_back(p);
                        capacities.push_back(cap);
                    }
                }
            }
            cout << "\nThe station/s that require more trains\nCapacity: " << max_trains << endl;
            for(int i = 0; i < sts.size(); i++){
                if(capacities[i] == max_trains){
                    cout << sts[i].first->getStation().name << " --> " << sts[i].second->getStation().name << endl;
                }
            }

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
    string source, sink;
    int s, t;
    cout << "#############################" << endl;
    cout << "#           Menu 2          #" << endl;
    cout << "#############################" << endl;
    cout << "Source: ";
    cin.ignore(); getline(cin, source, '\n');
    cout << "Destination: ";
    getline(cin, sink, '\n');
    for (auto e: tN.getGraph()->stations_) {
        if (source == e.second) {
            s = e.first;
        }
        if (sink == e.second) {
            t = e.first;
        }
    }
    cout << "The minimal cost between " << source << " and " << sink << " is " << tN.getGraph()->minCost(s, t) << endl;


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