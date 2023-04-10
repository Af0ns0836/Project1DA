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

int Graph::maxFlow(int source, int target) {
    ///Setting source&target vertex
    Vertex *u = findVertex(target);
    ///
    edmondsKarp(source, target);
    int flow = 0;
    for (auto e : u->getIncoming() ) flow += e->getFlow();
    return flow;
}
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


Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

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
void Graph::augmentFlow(Vertex* dest, int flow) const {
    auto v = dest;
    auto e = v->getPath();

    while (e != nullptr) {
        e->getOrig() == v ? e->setFlow(e->getFlow() - flow) : e->setFlow(e->getFlow() + flow);

        v = e->getOrig() == v ? e->getDest() : e->getOrig();

        e = v->getPath();
    }
}

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