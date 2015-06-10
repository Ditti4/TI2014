#include "vogel.h"

CVogel::CVogel(string name) : CTier(name) {}

void CVogel::KannEtwas() {
    cout << m_strName << " kann fliegen." << endl;
}