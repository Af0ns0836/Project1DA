//
// Created by dias4 on 18/03/2023.
//


#include "TrainNetwork.h"

int main(){
    TrainNetwork tN= TrainNetwork();
    string file = "../data/stations2.csv", file2 = "../data/network2.csv";
    tN.readStations(file);
    tN.readNetwork(file2);
    tN.menu();
    return 0;
}
