#include "fisch.h"

CFisch::CFisch(string name) : CTier(name) {}

void CFisch::KannEtwas() {
    cout << m_strName << " kann schwimmen." << endl;
}