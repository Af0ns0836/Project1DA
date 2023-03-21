//
// Created by dias4 on 18/03/2023.
//

#include "Menu.h"
#include "TrainNetwork.h"

int main(){
    TrainNetwork trainNetwork = TrainNetwork();
    string file = "../data/stations.csv";
    trainNetwork.readStations(file);
    menu();
    return 0;
}
