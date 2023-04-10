//
// Created by dias4 on 20/03/2023.
//

#ifndef PROJECT1DA_TRAINNETWORK_H
#define PROJECT1DA_TRAINNETWORK_H

#include "Graph.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

class TrainNetwork{

private:

    Graph* graph;

public:

    TrainNetwork();

    ~TrainNetwork();

    void readStations(string& filename);

    void readNetwork(string &line_filename);

    Graph * getGraph() ;

    void setGraph(Graph *graph);

    vector<Line> lines_;

    bool compareStations(const pair<string, int>& a, const pair<string, int>& b);

    void SortStations(int k);
};

#endif //PROJECT1DA_TRAINNETWORK_H
