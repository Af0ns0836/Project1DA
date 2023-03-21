//
// Created by dias4 on 20/03/2023.
//
#include "TrainNetwork.h"
#include <math.h>

TrainNetwork::TrainNetwork(){graph = nullptr;}

void TrainNetwork::readStations(string &filename){
    vector<Station> stations;
    ifstream in(filename);

    string dummy;

    string name;
    string district;
    string municipality;
    string township;
    string line;

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
        stations.push_back(station);

    }

    graph = new Graph(stations.size(), true);
    graph->setStation(stations);

}

void TrainNetwork::readNetwork(string &line_filename, string &line_name)
{
    int curr_station_index, next_station_index;

    string curr_station, next_station;
    ifstream line(line_filename);

    getline(line, curr_station);
    getline(line, curr_station);
    curr_station = graph->getStationName(curr_station);
    if (curr_station == "")
        return;


    while (getline(line, next_station) && next_station != " " && next_station != "\n")
    {

    }

}

Graph *TrainNetwork::getGraph(){
    return graph;
}

TrainNetwork::~TrainNetwork(){
    delete graph;
}