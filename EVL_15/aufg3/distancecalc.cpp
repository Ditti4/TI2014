#include "distancecalc.h"

int DistanceCalc::add_distance(string city1, string city2, float distance) {
    if(city1.empty() || city2.empty() || distance <= 0.0)
        return 1;
    distance_t temp;
    temp.city1 = city1;
    temp.city2 = city2;
    temp.distance = distance;
    distances.push_back(temp);
    return 0;
}

float DistanceCalc::get_distance(string city1, string city2) {
    for(vector<distance_t>::iterator it = distances.begin(); it != distances.end(); ++it) {
        if((it->city1 == city1 && it->city2 == city2) || (it->city1 == city2 && it->city2 == city1))
            return it->distance;
    }
    return -1.0;
}