// By: Gonçalo Leão

#include "Graph.h"

#include <utility>
/**
 * Returns the size of vertexSet
 * @return Size of vertexSet
 */
int Graph::getNumVertex() const {
    return vertexSet.size();
}
/**
 * Returns the vertexSet
 * @return VertexSet
 */
std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/**
 * Auxiliary function to find a vertex with a given content.
 * @param id - The desired id of the vertex
 * @return Vertex with desired id
 */
Vertex * Graph::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

/**
 * Finds the index of the vertex with a given content.
 * @param id - The desired id of the vertex
 * @return Index of the vertex with desired id
 */
int Graph::findVertexIdx(const int &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id)
            return i;
    return -1;
}
/**
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  @param id - The desired id of the vertex
 *  @param station - The desired station of the vertex
 *  @return True if the vertex was added, false if it already exists
 */
bool Graph::addVertex(const int &id, Station station) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id,station));
    return true;
}

/**
 * Adds an edge to a graph (this), given the contents of the source and destination vertices and the edge weight (w).
 * @param sourc - The desired id of the source vertex
 * @param dest - The desired id of the destination vertex
 * @param w - The desired weight of the edge
 * @param service - The desired service of the edge
 * @return True if the edge was added, false if the source or destination vertices do not exist
 */
bool Graph::addEdge(const int &sourc, const int &dest, double w, string service) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, service);
    return true;
}

/**
 * Adds a bidirectional edge to a graph (this), given the contents of the source and destination vertices and the edge weight (w).
 * @param sourc - The desired id of the source vertex
 * @param dest - The desired id of the destination vertex
 * @param w - The desired weight of the edge
 * @param service - The desired service of the edge
 * @return True if the edge was added, false if the source or destination vertices do not exist
 */
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

/**
 * Finds the maximum number of trains between all pairs of stations.
 * Complexity: O(V^3E^2)
 * @param edges - Vector of pairs of vertices used to return the edges that support the maximum number of trains
 * @return Maximum number of trains
 */
int Graph::maxTrains(vector<pair<Vertex*,Vertex*>> *edges) {
    vector<pair<Vertex*,Vertex*>> sts;
    vector<int> capacities;
    int max_trains = vertexSet[0]->getAdj()[0]->getWeight();
    for(int i = 0; i < getNumVertex(); i++){
        for(int j = i+1; j < getNumVertex(); j++){
            int cap = maxFlow(vertexSet[i]->getId(), vertexSet[j]->getId());
            if(cap >= max_trains){
                max_trains = cap;
                pair<Vertex*,Vertex*> p(vertexSet[i],vertexSet[j]);
                sts.push_back(p);
                capacities.push_back(cap);
            }
        }
    }
    for(int i = 0; i < sts.size(); i++){
        if(capacities[i] == max_trains){
            edges->push_back(sts[i]);
        }
    }
    return max_trains;
}

/**
 * Tests if a vertex is reachable from another vertex - if it is, visits it.
 * @param q - Queue of vertices
 * @param e - Next vertex
 * @param w - Current vertex
 * @param residual - Residual capacity
 */
void Graph::testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual) {
    if (! w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

/**
 * Finds the augmenting path between two vertices.
 * @param s - Source vertex
 * @param t - Destination vertex
 * @return True if it reaches the sink vertex, false otherwise
 */
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

/**
 * Finds the minimum residual capacity along the augmenting path.
 * @param s - Source vertex
 * @param t - Destination vertex
 * @return Minimum residual capacity
 */
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

/**
 * Augments the flow along the augmenting path.
 * @param s - Source vertex
 * @param t - Destination vertex
 * @param f - Flow to be augmented
 */
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


int Graph::findBottleneck(Vertex* s) const {
    int cap = numeric_limits<int>::max();
    int tmp;
    auto v = s;
    auto e = v->getPath();

    while (e != nullptr) {
        tmp = e->getOrig() == v ? e->getFlow() : e->getWeight() - e->getFlow() - e->getReverse()->getFlow();

        if (tmp < cap)
            cap = tmp;

        v = e->getOrig() == v ? e->getDest() : e->getOrig();

        e = v->getPath();
    }

    return cap;
}


/**
 * Sets the flow along the path from source to sink.
 * @param source - Source vertex
 * @param target - Destination vertex
 */

void Graph::edmondsKarp(int source, int target) {
    Vertex* s = findVertex(source);
    Vertex* t = findVertex(target);
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


/**
 * Executes a Breath-First Search on the graph.
 * Complexity: O(V+E)
 * @param s - Source vertex
 * @param u - Sink vertex
 * @return True if the sink is reachable from the source, false otherwise
 */
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

/**
 * Uses Edmond's Karp algorithm to find the maximum flow between two vertices.
 * Complexity: O(VE^2)
 * @param source - Source vertex
 * @param target - Destination vertex (Sink)
 * @return Maximum flow
 */

int Graph::maxFlow(int source, int target) {
    ///Setting source&target vertex
    Vertex *u = findVertex(target);
    ///
    edmondsKarp(source, target);
    int flow = 0;
    for (auto e : u->getIncoming() ) flow += e->getFlow();
    return flow;
}
/**
 * Finds the minimum cost to travel between two vertices.
 * Complexity: O(E log(V))
 * @param source - Source vertex
 * @param target - Destination vertex
 * @return Minimum cost flow
 */
pair<int,int> Graph::minCost(int source, int target) {
    int minCost = 0, maxFlow = 0;
    for (auto v : vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
            //e->setVisited(false);
        }
    }
    pair<int,int> p;
    Vertex *s = findVertex(source);
    Vertex *u = findVertex(target);
    while (findCheapestPath(s, u)){
        int flow = findBottleneck(u);
        augmentFlow(u, flow);
    }
    queue<Vertex *> q;

    s->setVisited(true);
    q.push(s);
    Vertex *currNode;

    while (!q.empty()) {
        currNode = q.front();

        for (Edge *e: currNode->getAdj()) {
            Vertex *destNode = e->getDest();

            if (e->getFlow() > 0 && !e->getVisited()) {
                if (!destNode->isVisited()) {
                    q.push(destNode);
                    destNode->setVisited(true);
                }
                minCost += e->getFlow() * e->getServiceCost();
                e->setVisited(true);
            }
        }

        q.pop();
    }
    for (Edge *e: u->getIncoming()) {
        maxFlow += e->getFlow();
    }
    p = {maxFlow,minCost};
    return p;
}


/**
 * Deletes the graph
 */

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

/**
 * Uses Edmond's Karp algorithm to find the maximum flow between two vertices on the subgraph after removing the desired vertices/edges.
 * Complexity: O(VE^2)
 * @param stRemove - Vector of stations to be removed
 * @param source - Source vertex
 * @param target - Destination vertex (Sink)
 * @return Maximum flow
 */
int Graph::ReducedConnectityGraphFlow(vector<string> stRemove, int source, int target) {
    int s = 0, res = 0;
    for(auto st : stRemove){
        for (auto e: stations_) {
            if(st == e.second) s = e.first;
        }
        removeVertex(s);
    }
    res = maxFlow(source,target);
    return res;
}

/**
 * Removes a vertex from the graph.
 * @param id - ID of the vertex to be removed
 * @return Returns true if the vertex was removed, false otherwise
 */
bool Graph::removeVertex(const int &id) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getId() == id) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getId());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

/**
 * Finds the chepeast path between two vertices.
 * @param source - Source vertex
 * @param target - Destination vertex
 * @return True if the target vertex was reached, false otherwise
 */
bool Graph::findCheapestPath(Vertex *source, Vertex *target) {
    resetNodes();
    source->setCost(0);

    for (int i = 0; i < getVertexSet().size(); i++) {
        for (auto v: getVertexSet()) {
            Vertex *orig = v;

            for (Edge *e: orig->getAdj()) {
                Vertex *adjNode = e->getDest();
                Edge *reverse = e->getReverse();

                bool relaxEdge = adjNode->getCost() > orig->getCost() + e->getServiceCost();
                bool isNotFull = e->getWeight() > e->getFlow() + reverse->getFlow();

                if (relaxEdge && isNotFull) {
                    adjNode->setCost(orig->getCost() + e->getServiceCost());
                    adjNode->setPath(e);
                }
            }

            for (Edge *e: orig->getIncoming()) {
                Vertex *adjNode = e->getOrig();

                bool relaxEdge = adjNode->getCost() > orig->getCost() - e->getServiceCost();

                if (e->getFlow() > 0 && relaxEdge) {
                    adjNode->setCost(orig->getCost() - e->getServiceCost());
                    adjNode->setPath(e);
                }
            }
        }
    }

    return target->getPath() != nullptr;
}

/**
 * Augments the flow along the a vertex's path
 * @param dest - Destination vertex
 * @param flow - Flow to be augmented
 */
void Graph::augmentFlow(Vertex* dest, int flow) const {
    auto v = dest;
    auto e = v->getPath();

    while (e != nullptr) {
        e->getOrig() == v ? e->setFlow(e->getFlow() - flow) : e->setFlow(e->getFlow() + flow);

        v = e->getOrig() == v ? e->getDest() : e->getOrig();

        e = v->getPath();
    }
}

/**
 * Resets the nodes' visited, path and cost values.
 */
void Graph::resetNodes() const {
    for (auto v: getVertexSet()) {
        v->setVisited(false);
        v->setPath(nullptr);
        v->setCost(100000);

        for (Edge *e: v->getAdj()) {
            e->setVisited(false);
        }
    }
}