#ifndef __TIER_H
#define __TIER_H

#include "iostream"
#include <string>

using namespace std;

class CTier {
protected:
    string m_strName;
public:
    CTier(string name);
    virtual void KannEtwas() = 0;
};

#endif