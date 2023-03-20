#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Station.h"
#include <vector>
#include <list>
#include <iostream>
#include <climits>

using namespace std;


class Graph {

    struct Edge {
        int dest;   //Destination node
        float weight; //An integer weight
        string  station;
        bool operator<(const Edge& edge) const
        {
            return weight > edge.weight;
        }
    };

    struct Node {
        list<Edge> adj;     //The list of outgoing edges (to adjacent nodes)
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes;
    vector<Station> stations;

public:

    Graph(int nodes, bool dir = false);

    void addEdge(int src, int dest, float weight, string& line);

    void BFS(int startingNode);

    vector<Station>& getStations();

    void setStation(vector<Station>& stations);

    int getStationName(string &name);

    void printAdjancies(int node );
};

#endif
