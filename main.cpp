//
// Created by dias4 on 18/03/2023.
//

#include "Menu.h"
#include "TrainNetwork.h"

int main(){
    TrainNetwork trainNetwork = TrainNetwork();
    string file = "../data/stations.csv", file2 = "../data/network.csv", string1 = "Paulo bento";
    trainNetwork.readStations(file);
    trainNetwork.readNetwork(file2,string1);
    menu();
    return 0;
}
