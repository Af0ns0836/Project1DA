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

void Graph::testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual) {
    if (! w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool Graph::findAugmentingPath(Vertex *s, Vertex *t) {
    for(auto v : vertexSet) {
        v->setVisited(false);
    }
    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
    return t->isVisited();
}

double Graph::findMinResidualAlongPath(Vertex *s, Vertex *t) {
    double f = INF;
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

void Graph::augmentFlowAlongPath(Vertex *s, Vertex *t, double f) {
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

void Graph::edmondsKarp(int source, int target) {
    Vertex* s = findVertex(source);
    Vertex* t = findVertex(target);
    int maxflow = 0;
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");

    // Reset the flows
    for (auto v : vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    // Loop to find augmentation paths
    while( findAugmentingPath(s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        maxflow += f;
        augmentFlowAlongPath(s, t, f);
    }
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
    edmondsKarp(source, target);
    int flow = 0;
    for (auto e : u->getIncoming() ) flow += e->getFlow();
    return flow;
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

