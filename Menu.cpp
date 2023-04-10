//
// Created by gonca on 4/10/2023.
//

#include "Menu.h"

void Menu::menu(){
    string stations = "../data/stations.csv", network = "../data/network.csv";
    TrainNetwork tn = TrainNetwork();
    tn.readStations(stations);
    tn.readNetwork(network);

    bool end = false;
    char option;
    while(!end){
        cout << "#############################" << endl;
        cout << "#         MAIN MENU         #" << endl;
        cout << "#############################" << endl;
        cout << "1.Basic Service Metrics" << endl;
        cout << "2.Operation Cost Optimization" << endl;
        cout << "3.Reliability and Sensitivity to Line Failures" << endl;
        cout << "4.Load Dataset" << endl;
        cout << "Enter q to terminate the program or to return to a previous menu" << endl;
        cout << "Enter the respective number: ";
        cin >> option;
        if(option == 'q') end = true;
        else if(option == '1'){
            menu1(&tn);
        }
        else if(option == '2'){
            menu2(&tn);
        }
        else if(option == '3'){
            menu3(&tn);
        }
        else if (option == '4') {
            menu4(&tn);
        }
    }
}

void Menu::menu1(TrainNetwork *tn){
    bool end = false;
    char option;
    while(!end){
        cout << "#############################" << endl;
        cout << "#   Basic Service Metrics   #" << endl;
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
            for (auto e: tn->getGraph()->stations_) {
                if (source == e.second) {
                    s = e.first;
                }
                if (sink == e.second) {
                    t = e.first;
                }
            }
            cout << "Max flow = " << tn->getGraph()->maxFlow(s,t) << endl;

            return;

        }
        else if(option == '2') {
            ///Function that computes maximum num of trains between all pairs of stations | Time complexity: O(V^3E^2)
            vector<pair<Vertex*,Vertex*>> sts;
            vector<int> capacities;
            int max_trains = tn->getGraph()->getVertexSet()[0]->getAdj()[0]->getWeight();
            for(int i = 0; i < tn->getGraph()->getNumVertex(); i++){
                for(int j = i+1; j < tn->getGraph()->getNumVertex(); j++){
                    int cap = tn->getGraph()->maxFlow(tn->getGraph()->getVertexSet()[i]->getId(), tn->getGraph()->getVertexSet()[j]->getId());
                    if(cap >= max_trains){
                        max_trains = cap;
                        pair<Vertex*,Vertex*> p(tn->getGraph()->getVertexSet()[i],tn->getGraph()->getVertexSet()[j]);
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
            tn->SortStations(k);
        }
        //meter as funcoes respetivas e isso

    }
}

void Menu::menu2(TrainNetwork *tn){
//meter as funcoes respetivas e isso
    string source, sink;
    int s, t;
    cout << "#############################" << endl;
    cout << "#Operation Cost Optimization#" << endl;
    cout << "#############################" << endl;
    cout << "Source: ";
    cin.ignore(); getline(cin, source, '\n');
    cout << "Destination: ";
    getline(cin, sink, '\n');
    for (auto e: tn->getGraph()->stations_) {
        if (source == e.second) {
            s = e.first;
        }
        if (sink == e.second) {
            t = e.first;
        }
    }
    cout << "The minimal cost between " << source << " and " << sink << " is " << tn->getGraph()->minCost(s, t) << endl;


}

void Menu::menu3(TrainNetwork *tn){
//meter as funcoes respetivas e isso

    bool end = false;
    char option;
    while(!end) {
        cout << "################################################" << endl;
        cout << "# Reliability and Sensitivity to Line Failures #" << endl;
        cout << "################################################" << endl;
        cout << "1.Maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity"<< endl;
        cout << "2.Stations that are most affected by each segment fail" << endl;
        cout << "Enter the respective number or q to return to the main menu: ";
        cin >> option;
        if (option == 'q') end = true;
        else if (option == '1') {
            vector<string> removeS;
            string stationR;
            bool d = true;
            int f = 0;
            cout << "When you are done removing stations enter d " << endl;
            cin.ignore();
            while(d){
                cout << "Input a station to remove: ";
                getline(cin, stationR, '\n');
                if(stationR == "d") d = false;
                removeS.push_back(stationR);
            }
            string source, sink;
            int s, t;
            cout << "Source: ";
            getline(cin, source, '\n');
            cout << "Sink: ";
            getline(cin, sink, '\n');
            for (auto e: tn->getGraph()->stations_) {
                if (source == e.second) {
                    s = e.first;
                }
                if (sink == e.second) {
                    t = e.first;
                }
            }
            cout << "The max flow in the reduced connectivity graph is: " << tn->getGraph()->ReducedConnectityGraphFlow(removeS,s,t) << endl;
            cout << "If you want to use the original graph choose Load Dataset from the main menu and proceed to load the data from there" << endl;
            return;

        } else if (option == '2') {
            //meter as funcoes respetivas e isso

        }
    }
}

void Menu::menu4(TrainNetwork *tn) {
    string stations, network;
    bool end = false;
    char option;
    while (!end) {
        cout << "#############################" << endl;
        cout << "#        Load Dataset       #" << endl;
        cout << "#############################" << endl;
        cout << "1.Load Data from preset" << endl;
        cout << "2.Load Data from my own dataset" << endl;
        cout << "Enter the respective number or q to return to the main menu: ";
        cin >> option;
        if (option == 'q') {
            end = true;
        }
        else if (option == '1') {
            stations = "../data/stations.csv";
            network = "../data/network.csv";
            TrainNetwork temp = TrainNetwork();
            temp.readStations(stations);
            temp.readNetwork(network);
            tn = &temp;
            return;
        }
        else if (option == '2') {
            string stationsPath = "../data/";
            string networkPath = "../data/";
            cout << "Stations file name (extention included): ";
            cin.ignore(); getline(cin, stations, '\n');
            cout << "Network file name (extention included): ";
            getline(cin, network, '\n');

            stationsPath.append(stations);
            networkPath.append(network);

            TrainNetwork temp = TrainNetwork();
            temp.readStations(stationsPath);
            temp.readNetwork(networkPath);

            tn = &temp;
            return;
        }
    }
}