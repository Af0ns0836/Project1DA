//
// Created by dias4 on 18/03/2023.
//


#include "TrainNetwork.h"

int main(){
    TrainNetwork tN= TrainNetwork();
    string stations = "../data/stations.csv", network = "../data/network.csv";
    tN.readStations(stations);
    tN.readNetwork(network);
    tN.menu();
    return 0;
}
