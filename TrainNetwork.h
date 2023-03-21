//
// Created by dias4 on 20/03/2023.
//

#ifndef PROJECT1DA_TRAINNETWORK_H
#define PROJECT1DA_TRAINNETWORK_H

#include "graph.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class TrainNetwork{

private:

    Graph* graph;

public:

    TrainNetwork();

    ~TrainNetwork();

    void readStations(string& filename);

    void readNetwork(string& filename ,string& name);

    Graph * getGraph() ;

};

#endif //PROJECT1DA_TRAINNETWORK_H
