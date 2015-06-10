#include <iostream>
#include <string>

using namespace std;

template <class T>
class test {
public:
    void print_me(T var) {
        cout << var << endl;;
    }
};

int main(int argc, char **argv) {
    test<int> intprint;
    test<string> stringprint;
    test<float> floatprint;
    intprint.print_me(4);
    stringprint.print_me("test");
    floatprint.print_me(3.1415);
    return 0;
}
