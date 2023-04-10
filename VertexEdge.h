// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_VERTEX_EDGE
#define DA_TP_CLASSES_VERTEX_EDGE

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"
#include "Station.h"

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

class Vertex {
public:

    Vertex(int id, Station station);
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue
    int getId() const;
    int getCost() const;
    void setCost(int cost);

    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;
    void setVisited(bool visited);
    void setPath(Edge *path);
    Edge * addEdge(Vertex *dest, double , string service);
    bool removeEdge(int destID);
    void removeOutgoingEdges();
    Station getStation() const;

    friend class MutablePriorityQueue<Vertex>;


protected:
    int id;// identifier
    Station station_;
    std::vector<Edge *> adj;  // outgoing edges
    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    Edge *path = nullptr;
    int cost = 0;
    double dist = 0;
    std::vector<Edge *> incoming; // incoming edges
    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS
    void deleteEdge(Edge *edge);

};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w, string service);

    Vertex * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;
    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
    void addFlow(double flow);
    string getService() const;
    int getServiceCost() const;
    bool getVisited() const;
    void setVisited(bool visited);

protected:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity
    // auxiliary fields
    bool selected = false;
    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;
    double flow; // for flow-related problems
    string service;
    bool visited = false;

};

#endif /* DA_TP_CLASSES_VERTEX_EDGE */