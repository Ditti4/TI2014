#include <iostream>
#include <iomanip>

using namespace std;

class CMagQuadrat {
    int size;
    int **matrix;
public:
    CMagQuadrat(int n) {
        size = n;
        int i;
        matrix = new int*[size];
        for(i = 0; i < size; i++) {
            matrix[i] = new int[size];
        }
        generate_magic_square();
    }

    ~CMagQuadrat() {
        int i;
        for(i = 0; i < size; i++) {
            delete [] matrix[i];
            matrix[i] = NULL;
        }
        delete [] matrix;
        matrix = NULL;
    }

    void generate_magic_square() {
        int startingpoint_x = ((size - 1) / 2);
        int startingpoint_y = ((size - 3) / 2);
        int i, x = startingpoint_x, y = startingpoint_y;
        for(i = 1; i <= (size * size); i++) {
            if((i != 1) && i % size == 1) {
                x = startingpoint_x = (--startingpoint_x == -1) ? (size - 1) : startingpoint_x;
                y = startingpoint_y = (--startingpoint_y == -1) ? (size - 1) : startingpoint_y;
            }
            matrix[x][y] = i;
            x = (++x == size) ? 0 : x;
            y = (--y == -1) ? (size - 1) : y;
        }
    }

    void show_magic_square() {
        int x, y;
        cout << endl;
        for(y = 0; y < size; y++) {
            for(x = 0; x < size; x++) {
                cout << "\t" << matrix[x][y];
            }
            cout << endl;
        }
        cout << endl;
    }

    int get_sum() {
        int i, j, lastsum, sum;
        for(j = lastsum = sum = 0; j < size; j++) {
            for(i = sum = 0; i < size; i++) {
                sum += matrix[i][j];
            }
            if(lastsum == 0)
                lastsum = sum;
            else
                if(lastsum != sum)
                    return 0;
        }
        for(i = sum = 0; i < size; i++) {
            for(j = sum = 0; j < size; j++) {
                sum += matrix[i][j];
            }
            if(lastsum == 0)
                lastsum = sum;
            else
                if(lastsum != sum)
                    return 0;
        }
        return sum;
    }
};

int main(int argc, char **argv) {
    int size;
    cout << "Bitte Größe angeben: ";
    cin >> size;
    if(!(size % 2) || size <= 1) {
        cout << "Größe muss eine ungerade natürliche Zahl größer 0 sein." << endl;
        return 1;
    }
    CMagQuadrat square(size);
    square.show_magic_square();
    int sum = square.get_sum();
    if(sum == 0) {
        cout << "Summe stimmt nicht in jeder Zeile und Spalte überein." << endl;
        return 1;
    }
    cout << "Summe in jeder Zeile und Spalte: " << sum << endl;
    return 0;
}
