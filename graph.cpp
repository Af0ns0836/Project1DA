#include "graph.h"
#include <queue>
#include <algorithm>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1){}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, float weight, string &line)
{
    if (src < 0 || src > n - 1 || dest < 0 || dest > n - 1)
        return;
    nodes[src].adj.push_back({dest, weight,line});
    if (!hasDir)
        nodes[dest].adj.push_back({src, weight, line});
}

void Graph::setStation(vector<Station> &station)
{
    this->stations = station;
}

int Graph::getStationName(string &name) {
    for (int i = 0; i < stations.size(); i++)
        if (stations[i].name == name)
            return i;
    return -1;
}

vector<Station> &Graph::getStations() {
    return this->stations;
}


void Graph::printAdjancies(int node)
{
    cout << stations[node].name << " Has connections to :\n";
    for (Edge e : nodes[node].adj)
    {
        cout << stations[e.dest].name << ", ";
    }
}



