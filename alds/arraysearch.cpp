#include <iostream>

using namespace std;

template <class t> int find_in_array(t array[], t element, int size) {
    int pos = -1;
    for(int i = 0; i < size && pos == -1; i++) {
        if(array[i] == element)
            pos = i;
    }
    return pos;
}

int main(int argc, char **argv) {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << "Position, an der 4 gefunden wurde: " << find_in_array(array, 4, 9) << endl;
    return 0;
}
