// By: Gonçalo Leão

#include "Graph.h"

#include <utility>

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(const int &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id)
            return i;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const int &id, Station station) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id,station));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const int &sourc, const int &dest, double w, string service) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, service);
    return true;
}

bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double w,string service) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w, service);
    auto e2 = v2->addEdge(v1, w, service);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

///BFS | Time complexity: O(V+E)
bool Graph::bfs(Vertex *s, Vertex *u) {
    for(auto vert : vertexSet){
        vert->setVisited(false);
    }
    ///We start off by the Source vertex
    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);

    ///While we still have neighbors to visit and the sink hasn't been reached
    while(!q.empty() && !u->isVisited()){
        auto u = q.front();
        q.pop();
        ///Looks for the neighbors of the last visited vertex
        for(auto e : u->getAdj()){
            ///Checks if is not visited and if the flow is enough
            if((!e->getDest()->isVisited() && e->getWeight() - e->getFlow() > 0)){
                ///If so, updates the last visited vertex
                e->getDest()->setVisited(true);
                e->getDest()->setPath(e);
                q.push(e->getDest());
            }
        }
    }
    ///Checks if the sink vertex was reached
    return u->isVisited();
}
///Edmond´s Karp | Time Complexity: O(VE^2)
int Graph::maxFlow(int source, int target) {
    ///Setting source&target vertex
    Vertex *s = findVertex(source);
    Vertex *u = findVertex(target);

    ///
    for(int i = 0; i < getNumVertex(); i++){
        for(int j = 0; j < vertexSet[i]->getAdj().size(); j++){
            vertexSet[i]->getAdj()[j]->setFlow(0);
        }
    }
    ///Flow count
    double max_flow = 0, cost = 0;


    ///While there is an augmentative path
    while (bfs(s, u)) {

        double aug_flow = INF;

        ///Find out the bottleneck capacity of the path
        for(auto v = u; v != s; ){
            auto e = v->getPath();
            if (e->getDest() == v){
                aug_flow = std::min(aug_flow,e->getWeight() - e->getFlow());
                v = e->getOrig();
            }
            else{
                aug_flow = std::min(aug_flow,e->getFlow());
                v = e->getDest();
            }
        }
        ///Update the flow along the augmentative path
        for(auto v = u; v != s; ){
            auto e = v->getPath();
            double flow = e->getFlow();
            if (e->getDest() == v){
                e->setFlow(flow + aug_flow);
                v = e->getOrig();
            }
            else{
                e->setFlow(flow - aug_flow);
                v = e->getDest();
            }
        }
        ///Add the augmenting flow to the total
        max_flow += aug_flow;

    }
    ///Return the max flow
    return (int) max_flow;
}
int Graph::minCost(int source, int target) {
        // Find source and target vertices
        Vertex* s = findVertex(source);
        Vertex* t = findVertex(target);

        // Initialize flow and cost to zero
        double max_flow = 0.0;
        double total_cost = 0.0;

        // While there is an augmenting path from s to t
        while (bfs(s, t)) {
            // Compute bottleneck capacity of the augmenting path
            double bottleneck = INF;
            for (Vertex* v = t; v != s; v = v->getPath()->getReverse()->getDest()) {
                Edge* e = v->getPath();
                double residual = e->getWeight() - e->getFlow();
                bottleneck = std::min(bottleneck, residual);
            }

            // Update flow and cost along the augmenting path
            for (Vertex* v = t; v != s; v = v->getPath()->getReverse()->getDest()) {
                Edge* e = v->getPath();
                if (e->getDest() == v) {
                    e->addFlow(bottleneck);
                    total_cost += e->getCost() * bottleneck;
                } else {
                    e->addFlow(bottleneck);
                    total_cost -= e->getCost() * bottleneck;
                }
            }

            // Add augmenting flow to total flow
            max_flow += bottleneck;
        }

        // Return total cost
        return total_cost;
}


Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

