// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include "MutablePriorityQueue.h"
#include "VertexEdge.h"
#include "Station.h"
/**
 * @brief The Graph class
 * This class represents the graph data structure
 */
class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(const int &id) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const int &id, Station station);
    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const int &sourc, const int &dest, double w, string service);
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w, string service);
    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;
    unordered_map<int,string> stations_;
    bool bfs(Vertex *s, Vertex *t);
    int maxFlow(int source, int target);
    int minCost(int source, int target);
    void testAndVisit(queue<Vertex *> &q, Edge *e, Vertex *w, double residual);
    bool findAugmentingPath(Vertex *s, Vertex *t);
    void augmentFlowAlongPath(Vertex *s, Vertex *t, double f);
    double findMinResidualAlongPath(Vertex *s, Vertex *t);
    void edmondsKarp(int source, int target);
    int ReducedConnectityGraphFlow(vector<string> stRemove, int source, int target);
    bool removeVertex(const int &id);
    int maxTrains(vector<pair<Vertex*,Vertex*>> *edges);

protected:
    std::vector<Vertex *> vertexSet;    // vertex set
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall
    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const int &id) const;

};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);


#endif /* DA_TP_CLASSES_GRAPH */