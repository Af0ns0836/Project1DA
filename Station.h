//
// Created by dias4 on 20/03/2023.
//

#ifndef PROJECT1DA_STATION_H
#define PROJECT1DA_STATION_H

#include <string>
#include <unordered_set>
#include "Line.h"

using namespace std;


struct Station{

    string name;
    string district;
    string municipality;
    string Township;
    string line;
    bool operator<(const Station& other) const {
        return name < other.name;
    }
};



#endif //PROJECT1DA_STATION_H
