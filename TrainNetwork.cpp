//
// Created by dias4 on 20/03/2023.
//
#include <functional>
#include "TrainNetwork.h"
#include "Station.h"


TrainNetwork::TrainNetwork(){ graph = new Graph(); }

void TrainNetwork::readNetwork(string &line_filename)
{
    string stationA, stationB, capacity,service;
    ifstream linha(line_filename);
    Line line_;
    int source = 0 , dest = 0;

    getline(linha, stationA);
   while(linha.peek() != EOF){
       getline(linha, stationA, linha.widen(','));
       getline(linha, stationB, linha.widen(','));
       getline(linha, capacity, linha.widen(','));
       getline(linha, service, linha.widen('\n'));

       line_ = {stationA, stationB,stoi(capacity),service};
        for(int j = 0;j < graph->getNumVertex(); j++){
            if(graph->stations_[j] == stationA)
                source = j;
            else if(graph->stations_[j] == stationB)
                dest = j;
        }
       graph->addBidirectionalEdge(source,dest,line_.capacity,line_.service);
   }
}

void TrainNetwork::readStations(string &filename){
    vector<Station> stations;
    ifstream in(filename);
    string file2 = "../data/network.csv", string1 = "Paulo bento";
    string name,district,municipality,township,line,dummy;
    //Line lines = readNetwork(file2,string1);
    getline(in, dummy);

    while (in.peek() != EOF)
    {
        //Name,District,Municipality,Township,Line
        getline(in, name, in.widen(','));
        getline(in, district, in.widen(','));
        getline(in, municipality, in.widen(','));
        getline(in, township, in.widen(','));
        getline(in, line, in.widen('\n'));

        Station station = {name, district, municipality, township, line};
        stations.push_back(station);
    }
    int i = 0;
    for(auto station : stations) {
        getGraph()->addVertex(i,station);
        i++;
    }
    pair<int,string> p;
    for (int i = 0; i < stations.size(); i++) {
        p.first = i; p.second = stations[i].name;
        graph->stations_.insert(p);
    }
    in.close();
}

bool TrainNetwork::compareStations(const pair<string,int>& a, const pair<string,int>& b){
    return a.second > b.second;
}

void TrainNetwork::SortStations(int k) {
    vector<pair<string,int>> nodes;
    auto vertex =  graph->getVertexSet();
    for(unsigned int i = 0; i < vertex.size(); i++){
        nodes.push_back(make_pair(vertex[i]->getStation().municipality,vertex[i]->getAdj().size()));
    }
    sort(nodes.begin(), nodes.end(), bind(&TrainNetwork::compareStations, this, placeholders::_1, placeholders::_2));
    cout << "The top " << k << " municipalities are" << endl;
    for(int j = 0; j < k ; j++){
        cout << nodes[j].first << endl;
    }
}

void TrainNetwork::menu(){
    bool end = false;
    char option;
    while(!end){
        cout << "#############################" << endl;
        cout << "#         MAIN MENU         #" << endl;
        cout << "#############################" << endl;
        cout << "1.Basic Service Metrics" << endl;
        cout << "2.Operation Cost Optimization" << endl;
        cout << "3.Reliability and Sensitivity to Line Failures" << endl;
        cout << "Enter q to terminate the program or to return to a previous menu" << endl;
        cout << "Enter the respective number: ";
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

void TrainNetwork::menu1(){
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
            for (auto e: getGraph()->stations_) {
                if (source == e.second) {
                    s = e.first;
                }
                if (sink == e.second) {
                    t = e.first;
                }
            }
            cout << "Max flow = " << getGraph()->maxFlow(s, t) << endl;

            return;

        }
        else if(option == '2') {
            ///Function that computes maximum num of trains between all pairs of stations | Time complexity: O(V^3E^2)
            vector<pair<Vertex*,Vertex*>> sts;
            vector<int> capacities;
            int max_trains = getGraph()->getVertexSet()[0]->getAdj()[0]->getWeight();
            for(int i = 0; i < getGraph()->getNumVertex(); i++){
                for(int j = i+1; j < getGraph()->getNumVertex(); j++){
                    int cap = getGraph()->maxFlow(getGraph()->getVertexSet()[i]->getId(), getGraph()->getVertexSet()[j]->getId());
                    if(cap >= max_trains){
                        max_trains = cap;
                        pair<Vertex*,Vertex*> p(getGraph()->getVertexSet()[i],getGraph()->getVertexSet()[j]);
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
            SortStations(k);
        }
        //meter as funcoes respetivas e isso

    }
}

void TrainNetwork::menu2(){
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
    for (auto e: getGraph()->stations_) {
        if (source == e.second) {
            s = e.first;
        }
        if (sink == e.second) {
            t = e.first;
        }
    }
    cout << "The minimal cost between " << source << " and " << sink << " is " << getGraph()->minCost(s, t) << endl;


}

void TrainNetwork::menu3(){
//meter as funcoes respetivas e isso

    bool end = false;
    char option;
    while(!end) {
        cout << "#############################" << endl;
        cout << "#           Menu 3          #" << endl;
        cout << "#############################" << endl;
        cout << "1.Maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity"
        << endl;
        cout << "2.Stations that are most affected by each segment fail" << endl;
        cout << "Enter the respective number or q to return to the main menu: ";
        cin >> option;
        if (option == 'q') end = true;
        else if (option == '1') {
            string source, sink;
            int s, t;
            cout << "Source: ";
            cin.ignore(); getline(cin, source, '\n');
            cout << "Sink: ";
            getline(cin, sink, '\n');
            for (auto e: getGraph()->stations_) {
                if (source == e.second) {
                    s = e.first;
                }
                if (sink == e.second) {
                    t = e.first;
                }
            }
            cout << "Max flow = " << getGraph()->maxFlow(s, t) << endl;
            return;

        } else if (option == '2') {
            //meter as funcoes respetivas e isso

        }
    }
}

Graph *TrainNetwork::getGraph(){
    return graph;
}

TrainNetwork::~TrainNetwork(){
    delete graph;
}