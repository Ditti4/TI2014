#ifndef __DISTANCE_CALC_H
#define __DISTANCE_CALC_H

#include <string>
#include <vector>

using namespace std;

typedef struct __distance {
    string city1;
    string city2;
    float distance;
} distance_t;

class DistanceCalc {
    vector<distance_t> distances;
public:
    int add_distance(string city1, string city2, float distance);
    float get_distance(string city1, string city2);
};

#endif