#include <functional>
#include <set>
#include "TrainNetwork.h"
#include "Station.h"

/**
 * @brief TrainNetwork::TrainNetwork
 * This is the TrainNetwork constructor, where its original graph is created.
 */
TrainNetwork::TrainNetwork(){ graph = new Graph(); }

/**
 * @brief TrainNetwork::readNetwork
 * This function reads the network file and creates the edges of the graph.
 * @param line_filename - the name of the network file
 */
void TrainNetwork::readNetwork(string &line_filename)
{
    string stationA, stationB, capacity,service;
    ifstream linha(line_filename);
    Line line_;
    int source = 0 , dest = 0;

    getline(linha, stationA);
   while(linha.peek() != EOF){
       getline(linha, stationA, linha.widen(','));
       getline(linha, stationB, linha.widen(','));
       getline(linha, capacity, linha.widen(','));
       getline(linha, service, linha.widen('\n'));

       line_ = {stationA, stationB,stoi(capacity),service};
        for(int j = 0;j < graph->getNumVertex(); j++){
            if(graph->stations_[j] == stationA)
                source = j;
            else if(graph->stations_[j] == stationB)
                dest = j;
        }
       graph->addBidirectionalEdge(source,dest,line_.capacity,line_.service);
   }
}

/**
 * @brief TrainNetwork::readStations
 * This function reads the stations file and creates the vertices of the graph.
 * @param filename - the name of the stations file
 */
void TrainNetwork::readStations(string &filename){
    vector<Station> stations;
    set<Station> unique_stations;
    ifstream in(filename);
    string name,district,municipality,township,line,dummy;
    getline(in, dummy);

    while (in.peek() != EOF)
    {
        //Name,District,Municipality,Township,Line
        getline(in, name, in.widen(','));
        getline(in, district, in.widen(','));
        getline(in, municipality, in.widen(','));
        getline(in, township, in.widen(','));
        getline(in, line, in.widen('\n'));

        Station station = {name, district, municipality, township, line};
        auto [it, success] = unique_stations.insert(station);
        if (success) {
            stations.push_back(station);
        }
    }

    int i = 0;
    for(auto station : stations) {
        getGraph()->addVertex(i,station);
        i++;
    }
    pair<int,string> p;
    for (int i = 0; i < stations.size(); i++) {
        p.first = i; p.second = stations[i].name;
        graph->stations_.insert(p);
    }
    in.close();
}

/**
 * @brief TrainNetwork::compareStations
 * This function compares two stations, using the alphabetical order of their names.
 * @param a - the first station
 * @param b - the second station
 * @return True if the first station is alphabetically before the second station, false otherwise
 */
bool TrainNetwork::compareStations(const pair<string,int>& a, const pair<string,int>& b){
    return a.second > b.second;
}

/**
 * @brief TrainNetwork::SortStations
 * This function sorts the stations by the number of connections they have.
 * @param k - the number of stations to be printed
 */
void TrainNetwork::SortStations(int k) {
    vector<pair<string,int>> nodes;
    auto vertex =  graph->getVertexSet();
    for(unsigned int i = 0; i < vertex.size(); i++){
        nodes.push_back(make_pair(vertex[i]->getStation().municipality,vertex[i]->getAdj().size()));
    }
    sort(nodes.begin(), nodes.end(), bind(&TrainNetwork::compareStations, this, placeholders::_1, placeholders::_2));
    cout << "The top " << k << " municipalities are" << endl;
    for(int j = 0; j < k ; j++){
        cout << nodes[j].first << endl;
    }
}

/**
 * @brief TrainNetwork::getGraph
 * @return the graph of the TrainNetwork
 */
Graph *TrainNetwork::getGraph(){
    return graph;
}

/**
 * @brief TrainNetwork::setGraph
 * @param graph - the graph to be set
 */
void TrainNetwork::setGraph(Graph *graph) {
    this->graph = graph;
}

/**
 * @brief TrainNetwork::~TrainNetwork
 * This is the TrainNetwork destructor, where the graph is deleted.
 */
TrainNetwork::~TrainNetwork(){
    delete graph;
}