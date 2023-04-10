#ifndef PROJECT1DA_STATION_H
#define PROJECT1DA_STATION_H

#include <string>
#include <unordered_set>
#include "Line.h"

using namespace std;

/**
 * @brief Station Struct
 * @paragraph This struct represents a Train station.
 * @param name - Station's name
 * @param district - Station's district
 * @param municipality - Station's municipality
 * @param Township - Station's township
 * @param line - Station's line
 */
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
