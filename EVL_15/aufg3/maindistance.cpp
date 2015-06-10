#include <iostream>
#include "distancecalc.h"

int main(int argc, char **argv) {
    DistanceCalc dist;
    dist.add_distance("Koeln", "Muenchen", 480);
    dist.add_distance("Köln", "München", 480);
    dist.add_distance("Berlin", "Muenchen", 530);
    dist.add_distance("Berlin", "München", 530);
    dist.add_distance("Berlin", "Koeln", 500);
    dist.add_distance("Berlin", "Köln", 500);

    string city1;
    string city2;

    cout << "Erste Stadt eingeben: ";
    cin >> city1;
    cout << "Zweite Stadt eingeben: ";
    cin >> city2;

    float distance = dist.get_distance(city1, city2);
    if(distance == -1.0) {
        cout << "Städtekombination nicht gefunden." << endl;
        return 1;
    }
    cout << "Entfernung zwischen " << city1 << " und " << city2 << ": " << distance << " km" << endl;
}
