#include <iostream>
#include <string>

using namespace std;

template <class T>
class test {
public:
    test(T var) {
        cout << var << endl;;
    }
};

int main(int argc, char **argv) {
    test<int> intprint(4);
    test<string> stringprint("test");
    test<float> floatprint(3.1415926);
    return 0;
}
